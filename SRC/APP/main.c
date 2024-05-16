#include "../../HEADERS/MCAL/GPIO.h"
#include "../../SERVICES/Bit_Operations.h"
#include "../../HEADERS/HAL/LED_SWITCHES.h"
#include "../../SERVICES/tm4c123.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../HEADERS/MCAL/UART.h"
#include "../../HEADERS/HAL/GPS.h"

unsigned char button_in_sw1;
unsigned char button_in_sw2;
int  main(void)
{
		char gprmc_sentence[] = "$GPRMC,123456.789,A,1234.5678,N,5678.1234,E,...";

    float latitude=0.0, longitude=0.0;
	
	  double start_point_lat =0.0;
	  double start_point_long=0.0; //the coordinates of start point when switch is pressed
    double total_distance=0; //variable for accumalated distance
    double dest_distance=0;  // variable for dispalcement between start ponit and current point
    double current_Lat;
	  double current_Long;
	  double previous_Lat=0;
	  double previous_Long=0 ;
	  double destination_lat=0;
	  double destination_long=0;
    int i = 0;
    char c;
   	initialize_PortD();	
	  uart_init();
	  initialize_PortF ();
	  
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
               //printstring(gprmc_sentence);  
               extract_lat_lon( gprmc_sentence, &latitude, &longitude);
							if( start_point_lat==0&start_point_long==0){
							start_point_lat=latitude;
								start_point_long=longitude;
							
							}
							
               
						 	// printstring("latitude\n");
					   	 printFloat_UART0(latitude);
							 printstring(",");
						  // UART0_Transmitter('\n');
						   //printstring("longitude\n");
						   printFloat_UART0(longitude);
							 printstring(",");	
               printFloat_UART0(total_distance);
							 printstring(",");							
               printstring("\n");	
               printFloat_UART2 (total_distance);
							 UART2_Transmitter(',');							
               Systic_wait_1ms(50);
    current_Lat=latitude;//get from GPS reading
    current_Long=longitude;//get from GPS reading
			if( previous_Long==0&previous_Lat==0){
				 previous_Long=longitude;
        previous_Lat=latitude;
			
			}
    if(total_distance<100) // you don't exceed 100 meter
    {
        total_distance +=GPS_calc_distance(current_Lat ,current_Long ,previous_Lat, previous_Long );
        dest_distance=GPS_calc_distance(current_Lat ,current_Long ,start_point_lat, start_point_long );
        previous_Long=current_Long;
        previous_Lat=current_Lat;
        set_LED(LED_ON , Red_LED); // you don't arrive
    }
    else
    {
        total_distance +=0;
        set_LED(LED_OFF , Red_LED);
        set_LED(LED_ON , Green_LED); //you arrived!
        destination_lat= previous_Lat;  //last latitude is the destination latitiude
        destination_long=previous_Long; //last longitude is the destination longitude
    }}}}
 }
