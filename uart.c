#include "uart.h"
#define BAUD_PRESCALE ((F_CPU / (USART_BAUDRATE * 16UL)))
void UART_init(void){
	uint32_t m;SYSCTL_RCGCUART_R |= 0X01;	m=1;SYSCTL_RCGCGPIO_R |= 0X01; m=2;
	UART0_CTL_R &=~0X01;UART0_IBRD_R=52;UART0_FBRD_R=5;
	UART0_LCRH_R=0x0070;
	UART0_CTL_R=0X301;
	GPIO_PORTA_AFSEL_R|=0X03;
	GPIO_PORTA_PCTL_R=(GPIO_PORTA_PCTL_R & 0XFFFFFF00) + 0X11;
	GPIO_PORTA_DEN_R |=0X03;
	GPIO_PORTA_AMSEL_R &= ~0X03;
}
/*
void UART_sendByte(const uint8 data){
	while(BIT_IS_SET(UART1_FR_R,5)){}
	UART0_DR_R=data;	
}
*/
uint8 UART_recieveByte(void){
	while(BIT_IS_SET(UART0_FR_R,4)){}
		return (UART0_DR_R&0xff) ;}
/*
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}	
*/
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	
	Str[i] = UART_recieveByte();
	while(Str[i] != '#') ////// recieve data until '#'  
	{
		i++;		
		Str[i] = UART_recieveByte();
}
	Str[i] = '\0'; 
}	
