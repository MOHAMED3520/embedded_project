#include "../../SERVICES/tm4c123.h"
#include "../../SERVICES/Bit_Operations.h"
#include "../../HEADERS/HAL/LED_SWITCHES.h"


//**Get_switches_data**//
unsigned char read_switch_data(unsigned char sw){
	switch(sw){
		case SW1: return get_bit(GPIO_PORTF_DATA_R,4); break;
		case SW2: return get_bit(GPIO_PORTF_DATA_R,0); break;
		default: return 0;
	}
}

//**set_LEDs**//
void set_LED(unsigned char state , unsigned char color_LED){
	clear(GPIO_PORTF_DATA_R,0x0E); //reset all LEDs first
	if (color_LED == Red_LED) {
    if (state == LED_OFF) {
        clear_bit(GPIO_PORTF_DATA_R, 1); // turn red led off
    } 
		else if (state == LED_ON) {
        set_bit(GPIO_PORTF_DATA_R, 1); // turn red led on
    }
}
	else if (color_LED == Blue_LED) {
    if (state == LED_OFF) {
        clear_bit(GPIO_PORTF_DATA_R, 2); // turn blue led off
    } 
		else if (state == LED_ON) {
        set_bit(GPIO_PORTF_DATA_R, 2); // turn blue led on
    }
} 
	else if (color_LED == Green_LED) {
    if (state == LED_OFF) {
        clear_bit(GPIO_PORTF_DATA_R, 3); // turn green led off
    } 
		else if (state == LED_ON) {
        set_bit(GPIO_PORTF_DATA_R, 3); // turn green led on
    }
}
}