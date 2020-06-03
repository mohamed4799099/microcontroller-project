#ifndef UART_H_
#define UART_H_
#include "std_types.h"
#include "Common_macros.h"
#include "Microcontroller.h"
#define USART_BAUDRATE 9600
void UART_init(void);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str); // Receive until #
#endif /* UART_H_ */