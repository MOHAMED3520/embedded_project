
void Delay(unsigned long counter);
char UART1_Receiver(void);
void UART0_Transmitter(unsigned char data);
void UART2_Transmitter(unsigned char data);
void printstring(char *str);
void printstring_U2(char *str);
void printFloat_UART0(float number);
void printFloat_UART2(float number);
void uart_init(void);
