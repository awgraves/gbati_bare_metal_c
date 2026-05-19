#ifndef __UART_H__
#define __UART_H__
#include "stm32f446xx.h"

void uart_init(void);
void uart_print(const char *);
void uart_echo(void);

#endif // __USART_H__
