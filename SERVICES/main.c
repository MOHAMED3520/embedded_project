#include "TM4C123.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 80
#include <math.h>
#define pi 3.141592654
const double Earth_radius =6371000;



void Delay(unsigned long counter);
char UART1_Receiver(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void extract_lat_lon( const char *gprmc_sentence, float *latitude, float *longitude);
void printFloat_UART5(float number);
void uart_init(void);
float convertToFloat(const char* part);
float GPS_calc_distance(float current_Lat,float current_Long,float previous_Lat,float previous_Long);
float convert_to_Rad(float degree) ;
float ToDegree(float val);
float convertToFloat(const char* part);


int main(void)
{
		char gprmc_sentence[] = "$GPRMC,123456.789,A,1234.5678,N,5678.1234,E,...";

    float latitude, longitude;
	  float prev_latitude = 3014.190430;
	  float prev_longitude = 3126.626221;


    int i = 0;
    char c;	
	float x;
	  uart_init();
    Delay(1); 
    printstring("Hello World \n");
    Delay(10); 
		

    while(1)
    {
         c = UART1_Receiver(); /* get a character from UART1 */
        if(c == '$') {
            i = 0; /* reset index if we found a new sentence starting */
        }
        *(gprmc_sentence+i) = c;
        i++;
        if(c == '\n') { /* end of sentence */
           gprmc_sentence[i] = '\0'; /* null terminate the string */
            /* check if it's a GPRMC sentence */
					    if (gprmc_sentence[0] == '$' && gprmc_sentence[1] == 'G' && gprmc_sentence[2] == 'P' &&
                  gprmc_sentence[3] == 'R' && gprmc_sentence[4] == 'M' && gprmc_sentence[5] == 'C') {
               printstring(gprmc_sentence);
							 UART5_Transmitter('\n');  
                /* Now you can use the latitude and longitude values as needed /              / send the character to UART5 */
               extract_lat_lon( gprmc_sentence, &latitude, &longitude);

						 	 printstring("latitude\n");
					   	 printFloat_UART5(latitude);
						   UART5_Transmitter('\n');
						   printstring("longitude\n");
						   printFloat_UART5(longitude);
						   UART5_Transmitter('\n');
										
							
										x =GPS_calc_distance(latitude , longitude , prev_latitude , prev_longitude);
              printf("%f \n",x);



					 
									}else {
        // Invalid GPRMC sentence
        latitude = 0.0f;
        longitude = 0.0f;
    }
						
   }
  }
}
char UART1_Receiver(void)  
{
    char data;
    while((UART1->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART1->DR ;  /* before giving it another byte */
    return (unsigned char) data; 
}


void UART5_Transmitter(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

void printstring(char *str)
{
    while(*str)
    {
        UART5_Transmitter(*(str++));
    }
}

void Delay(unsigned long counter)
{
    unsigned long i = 0;
    
    for(i=0; i< counter; i++);
}



 void printFloat_UART5(float number) {
	 char buffer[50];
   char *r = buffer; 	 
    sprintf(buffer, "%f", number); /* convert the float to a string */


    while(*r != '\0') {
        UART5_Transmitter(*r); /* send each character of the string */
        r++;
    }
}



void uart_init(void){
    SYSCTL->RCGCUART |= 0x22;  /* enable clock to UART1 and UART5 */
    SYSCTL->RCGCGPIO |= 0x12;  /* enable clock to PORTB for UART1 and PORTE for UART5 */
    Delay(1);
    /* UART1 initialization */
    UART1->CTL = 0;         /* UART1 module disable */
    UART1->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART1->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART1->CC = 0;          /*select system clock*/
    UART1->LCRH = 0x60;     /* data length 8-bit, not parity bit, no FIFO */
    UART1->CTL = 0x301;     /* Enable UART1 module, Rx and Tx */

    /* UART1 RX1 use PB0. Configure them digital and enable alternate function */
    GPIOB->DEN = 0x01;      /* set PB0 as digital */
    GPIOB->AFSEL = 0x01;    /* Use PB0 alternate function */
    GPIOB->AMSEL = 0;    /* Turn off analog function*/
    GPIOB->PCTL = 0x00000001;     /* configure PB0 for UART */


    /* UART5 initialization */
    UART5->CTL = 0;         /* UART5 module disable */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          /*select system clock*/
    UART5->LCRH = 0x60;     /* data length 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 use PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x20;      /* set PE5 as digital */
    GPIOE->AFSEL = 0x20;    /* Use PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analog function*/
    GPIOE->PCTL = 0x00100000;     /* configure PE5 for UART */
	  } 

		
		
void SystemInit(void)
{
    __disable_irq();    /* disable all IRQs */
    
    /* Grant coprocessor access */
    /* This is required since TM4C123G has a floating point coprocessor */
    SCB->CPACR |= 0x00F00000;
}

float convertToFloat(const char* part) {
    float f;
    sscanf(part, "%f", &f);
    return f;
}
void extract_lat_lon(const char *gprmc_sentence, float *latitude, float *longitude) {
    // Check if the sentence starts with "$GPRMC" and has at least 8 parts

//char gprmc_sentence[] = "$GPRMC,123456.789,A,1234.5678,N,5678.1234,E,...";
        // Find the comma positions



	 
    char* rest = (char*)gprmc_sentence;
    char* comma1=( strtok_r(rest, ",", &rest));
    char* comma2=( strtok_r(rest, ",", &rest));
    char* comma3=( strtok_r(rest, ",", &rest));
    char* comma4=(strtok_r(rest, ",", &rest));
	  char* comma5=( strtok_r(rest, ",", &rest));
	  char* comma6=( strtok_r(rest, ",", &rest));
	  char* comma7=( strtok_r(rest, ",", &rest));


        if (comma1 && comma2 && comma3 && comma4 &&comma5&&comma6&&comma7 ) {
            // Extract latitude and longitude
            float lat_deg = convertToFloat(comma4 );
            char lat_dir = *(comma5 );
            float lon_deg = convertToFloat(comma6 );
            char lon_dir = *(comma7 );

            // Set latitude and longitude directly
            *latitude = lat_deg;
            
            if (lat_dir == 'S' || lat_dir == 's') {
                *latitude *= -1;
            }

            *longitude = lon_deg;
            

            if (lon_dir == 'W' || lon_dir == 'w') {
                *longitude *= -1;
            }
        } else {
            // Invalid GRMC sentence
            *latitude = 0;
            *longitude = 0;
        }
    }


//*function to convert GPS values to degree*//
float ToDegree(float val) {
    float result=0;
    int degree = (int)val / 100;
    float minutes = val-(float)degree*100;
    result = degree+ (minutes/60);
    return result;
}
//*function to Convert Degree to Rad*//
float convert_to_Rad(float degree) {
    return degree * (pi / 180.0);
}
//*function to calculate distance between two locations using longitude and latitude in Radians*//
//  Haversine formula: a = sin (?f/2) + cos f1   cos f2   sin (??/2)
//  c = 2 * atan2(sqrt(a), sqrt(1 - a))
// distance = Earth radius *c
float GPS_calc_distance(float current_Lat,float current_Long,float previous_Lat,float previous_Long){
    float prev_lat_rad = convert_to_Rad(ToDegree(previous_Lat));
    float prev_long_rad = convert_to_Rad(ToDegree(previous_Long));
    float current_lat_rad = convert_to_Rad(ToDegree(current_Lat));
    float current_long_rad = convert_to_Rad(ToDegree(current_Long));
    float lat_diff = current_lat_rad - prev_lat_rad;
    float long_diff = current_long_rad - prev_long_rad;

    float a= pow(sin(lat_diff/2),2)+cos(prev_lat_rad)*cos(current_lat_rad)*pow(sin(long_diff/2),2); // Haversine formula: a = sin (?f/2) + cos f1   cos f2   sin (??/2)
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return Earth_radius*c;   //in meters
}

