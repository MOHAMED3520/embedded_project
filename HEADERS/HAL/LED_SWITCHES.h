#include "../MCAL/GPIO.h"
//**PortF switches**//
#define SW1 4
#define SW2 0
#define SW_Pressed 0

//**PortF LEDs**//
#define Red_LED 1
#define Blue_LED 2
#define Green_LED 3
#define LED_ON 1
#define LED_OFF 0

unsigned char read_switch_data(unsigned char sw); //read switch input

void set_LED(unsigned char state , unsigned char color_LED); //set_LED