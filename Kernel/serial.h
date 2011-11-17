#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "circular.h"

#include <avr/io.h>

#ifdef USE_USART0
/* We use the <util/setbaud.h> macros now */
#if ! defined(USART0_BAUD)
#error Define USART0 Baudrate in Makefile
#endif

void initUSART0(void);
void transmitStringUSART0(char const * msg);
void transmitBufferUSART0(uint8_t const buffer[], uint8_t buffer_length);
void transmitIntegerUSART0(int value, int radix);

int USART0EnQueue( uint8_t data );
int USART0DeQueue( );
#endif

#ifdef USE_USART1

#if ! defined(USART1_BAUD)
#error Define USART1 Baudrate in Makefile
#endif

void initUSART1(void);
void transmitBufferUSART1(uint8_t const buffer[], uint8_t buffer_length);
void transmitStringUSART1(char const * msg);
void transmitIntegerUSART1(int value, int radix);

int USART1EnQueue( uint8_t data );
int USART1DeQueue( );
#endif

#endif /* SERIAL_H_ */
