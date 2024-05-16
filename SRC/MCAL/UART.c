#include<stdint.h>
#include "../../SERVICES/tm4c123.h"
#include "../../HEADERS/MCAL/UART.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//void Delay(unsigned long counter);
	 
void uart_init(void) {
    // Enable clock to UART0 and UART1
    SYSCTL_RCGCUART_R |= 0x03;  // Bit 0 for UART0, Bit 1 for UART1
    SYSCTL_RCGCGPIO_R |= 0x03;  // Enable clock to PORTA (UART0) and PORTB (UART1)
    //Delay(1);  // Delay for stabilization
    while(SYSCTL_PRGPIO_R & 0X03==0);

    // UART0 initialization
    UART0_CTL_R = 0;           // Disable UART0 module
    UART0_IBRD_R = 104;        // Integer part of the baud rate divisor (9600 baud rate)
    UART0_FBRD_R = 11;         // Fractional part of the baud rate divisor
    UART0_CC_R = 0;            // Use system clock
    UART0_LCRH_R = 0x70;       // 8-bit data, no parity, enable FIFO
    UART0_CTL_R = 0x301;       // Enable UART0 module, Rx and Tx

    // Configure UART0 RX0 (PA0) and TX0 (PA1) as digital and enable alternate function
    GPIO_PORTA_DEN_R |= 0x03;  // Set PA0 and PA1 as digital
    GPIO_PORTA_AFSEL_R |= 0x03;  // Use alternate function for PA0 and PA1
    GPIO_PORTA_PCTL_R |= 0x00000011;  // Configure PA0 and PA1 for UART0

      //UART1 initialization
      UART1_CTL_R = 0;           // Disable UART1 module
      UART1_IBRD_R = 104;        // Integer part of the baud rate divisor (9600 baud rate)
      UART1_FBRD_R = 11;         // Fractional part of the baud rate divisor
      UART1_CC_R = 0;            // Use system clock
      UART1_LCRH_R = 0x70;       // 8-bit data, no parity, enable FIFO
      UART1_CTL_R = 0x301;       // Enable UART1 module, Rx and Tx

    // Configure UART1 RX1 (PB0) and TX1 (PB1) as digital and enable alternate function
    GPIO_PORTB_DEN_R |= 0x03;  // Set PB0 and PB1 as digital
    GPIO_PORTB_AFSEL_R |= 0x03;  // Use alternate function for PB0 and PB1
    GPIO_PORTB_PCTL_R |= 0x00000011;  // Configure PB0 and PB1 for UART1
		
		// UART2 initialization
    SYSCTL_RCGCUART_R |= 0x04;  // Bit 2 for UART2
    SYSCTL_RCGCGPIO_R |= 0x04;  // Enable clock to PORTD (UART2)
    UART2_CTL_R = 0;           // Disable UART2 module
    UART2_IBRD_R = 104;        // Integer part of the baud rate divisor (9600 baud rate)
    UART2_FBRD_R = 11;         // Fractional part of the baud rate divisor
    UART2_CC_R = 0;            // Use system clock
    UART2_LCRH_R = 0x70;       // 8-bit data, no parity, enable FIFO
    UART2_CTL_R = 0x301;       // Enable UART2 module, Rx and Tx

    // Configure UART2 RX2 (PD6) and TX2 (PD7) as digital and enable alternate function
    GPIO_PORTD_DEN_R |= 0xC0;  // Set PD6 and PD7 as digital
    GPIO_PORTD_AFSEL_R |= 0xC0;  // Use alternate function for PD6 and PD7
    GPIO_PORTD_PCTL_R |= 0x11000000;  // Configure PD6 and PD7 for UART2
		
		
		

}


char UART1_Receiver(void)  
{
    char data;
    while((UART1_FR_R  & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART1_DR_R  ;  /* before giving it another byte */
    return (unsigned char) data; 
}


void UART0_Transmitter(unsigned char data)  
{
    while((UART0_FR_R  & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART0_DR_R  = data;                  /* before giving it another byte */
}
void UART2_Transmitter(unsigned char data)  
{
    while((UART2_FR_R  & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART2_DR_R  = data;                  /* before giving it another byte */
}

void printstring(char *str)
{
    while(*str)
    {
        UART0_Transmitter(*(str++));
    }
}
void printstring_U2(char *str)
{
    while(*str)
    {
        UART2_Transmitter(*(str++));
    }
}

void printFloat_UART0(float number) {
    char buffer[50];
    char *r = buffer;
    int integerPart, fractionalPart;

    // Handle negative numbers
    if (number < 0) {
        UART0_Transmitter('-'); // Send the minus sign
        number = -number; // Convert to positive for further processing
    }

    // Extract integer and fractional parts
    integerPart = (int)number;
    fractionalPart = (int)((number - integerPart) * 100000); // Assuming 5 decimal places

    // Convert integer part to string
    sprintf(buffer, "%d.", integerPart);
    while (*r != '\0') {
        UART0_Transmitter(*r);
        r++;
    }

    // Convert fractional part to string (ensure 5 digits)
    sprintf(buffer, "%05d", fractionalPart);
    r = buffer;
    while (*r != '\0') {
        UART0_Transmitter(*r);
        r++;
    }
}
 
void printFloat_UART2(float number) {
    char buffer[50];
    char *r = buffer;
    int integerPart, fractionalPart;

    // Handle negative numbers
    if (number < 0) { 
        UART2_Transmitter('-'); // Send the minus sign
        number = -number; // Convert to positive for further processing
    }

    // Extract integer and fractional parts
    integerPart = (int)number;
    fractionalPart = (int)((number - integerPart) * 100000); // Assuming 5 decimal places

    // Convert integer part to string
    sprintf(buffer, "%d.", integerPart);
    while (*r != '\0') {
        UART2_Transmitter(*r);
        r++;
    }

    // Convert fractional part to string (ensure 5 digits)
    sprintf(buffer, "%05d", fractionalPart);
    r = buffer;
    while (*r != '\0') {
        UART2_Transmitter(*r);
        r++;
    }}

/*
 void Delay(unsigned long counter)
{
    unsigned long i = 0;
    
    for(i=0; i< counter; i++);
}
*/

void Systic_Ini(void)
{
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R=0X00FFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0x05;
}
void Systic_Wait(uint32_t Delay)
{
	NVIC_ST_RELOAD_R=Delay-1;
	NVIC_ST_CURRENT_R=0;
	while( (NVIC_ST_CTRL_R & 0x00010000)==0);
}
uint32_t factor_1ms=16000; // 1ms / T(62.5ns)

// Total Delay = factor*1ms
void Systic_wait_1ms(uint32_t factor)
{
    unsigned long i;
    for(i=0;i<factor;i++)
    {
        Systic_Wait(factor_1ms); 
    }
}


