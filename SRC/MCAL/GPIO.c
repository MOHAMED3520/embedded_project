#include "../../SERVICES/tm4c123.h"
#include "../../SERVICES/Bit_Operations.h"
//**initialize portA**//
void initialize_PortA(){
set_bit(SYSCTL_RCGCGPIO_R,0); // BIT 0
while(get_bit(SYSCTL_PRGPIO_R,0)== 0);
GPIO_PORTA_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTA_CR_R |= 0xFF;
GPIO_PORTA_AMSEL_R &= 0x0; 
GPIO_PORTA_DIR_R |= 0x00; 
GPIO_PORTA_DEN_R |= 0xFF; 
}
//**initialize portB**//
void initialize_PortB(){
set_bit(SYSCTL_RCGCGPIO_R,1); // BIT 1
while(get_bit(SYSCTL_PRGPIO_R,1)== 0);
GPIO_PORTB_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTB_CR_R |= 0xFF;
GPIO_PORTB_AMSEL_R &= 0x0; 
GPIO_PORTB_DIR_R |= 0xFF; 
GPIO_PORTB_DEN_R |= 0xFF; 
}
//**initialize portC**//
void initialize_PortC(){
set_bit(SYSCTL_RCGCGPIO_R,2); // BIT 2
while(get_bit(SYSCTL_PRGPIO_R,2)== 0);
GPIO_PORTC_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTC_CR_R |= 0xFF;
GPIO_PORTC_AMSEL_R &= 0x0; 
GPIO_PORTC_DIR_R |= 0xFF; 
GPIO_PORTC_DEN_R |= 0xFF; 
}
//**initialize portD**//
void initialize_PortD(){
set_bit(SYSCTL_RCGCGPIO_R,3); // BIT 3
while(get_bit(SYSCTL_PRGPIO_R,3)== 0);
GPIO_PORTD_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTD_CR_R |= 0xFF;
GPIO_PORTD_AMSEL_R &= 0x0; 
GPIO_PORTD_DIR_R |= 0xFF; 
GPIO_PORTD_DEN_R |= 0xFF; 
}
//**initialize portE**//
void initialize_PortE(){
set_bit(SYSCTL_RCGCGPIO_R,4); // BIT 4
while(get_bit(SYSCTL_PRGPIO_R,4)== 0);
GPIO_PORTE_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTE_CR_R |= 0x3F;
GPIO_PORTE_AMSEL_R &= 0x0; 
GPIO_PORTE_DIR_R |= 0x3F; 
GPIO_PORTE_DEN_R |= 0xFF; 
}

//**initialize portF**//
void initialize_PortF (void){
	set_bit(SYSCTL_RCGCGPIO_R,5);   
	while(get_bit(SYSCTL_RCGCGPIO_R ,5)== 0); 	 
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;  
	GPIO_PORTF_CR_R = 0x1F;      
	GPIO_PORTF_AMSEL_R &= ~0x1F;
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;
	GPIO_PORTF_AFSEL_R &= ~0x1F;
	GPIO_PORTF_DEN_R |= 0x1F;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_DATA_R &= ~0x0E;
	GPIO_PORTF_PUR_R  |=0x11;
}