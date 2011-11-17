#include <string.h>
#include <stdlib.h>

#include "circular.h"
#include "serial.h"
#include "adc.h"
#include "led.h"

#include <avr/interrupt.h>

#if defined(USE_USART0)
   	struct CircularQueue USART0Queue;
#endif /* USE_USART0 */

#if defined(USE_USART1)
   	struct CircularQueue USART1Queue;
#endif /* USE_USART1 */

#if defined(USE_USART0)

void 
initUSART0(void) 
{
	initQueue( & USART0Queue );

	#undef BAUD
	#define BAUD USART0_BAUD
	#include <util/setbaud.h>

	// baud rate
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// double usart transmission speed
	#if USE_2X
		UCSR0A = (1 << U2X);
	#else
		UCSR0A = 0;
	#endif

	// rx complete interrupt
	// receiver
	// transmitter
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

	// 8N1
	// asynchronous
	// parity disabled
	// 1 stop bit
	// character size 8 bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
} // initUSART0

// atomic
void 
transmitBufferUSART0(uint8_t const buffer[], uint8_t buffer_length) 
{
	uint8_t x;

	for (x = 0; x < buffer_length; x++) {

//		UCSR0A |= (1 << TXC0);

		while ( !( UCSR0A & (1 << UDRE0) ) )
			asm volatile("nop"::);

		UDR0 = buffer[x];

	}

	while ( !( UCSR0A & (1 << TXC0) ) )
		asm volatile("nop"::);
} 

void 
transmitStringUSART0(char const * msg) 
{
    transmitBufferUSART0( (uint8_t *) msg, strlen(msg) );
} 

void 
transmitIntegerUSART0(int value, int radix) 
{
	char msg[17];
	itoa(value, msg, radix);
    transmitStringUSART0( msg );  
} 

int 
USART0EnQueue( uint8_t data )
{
	return enQueue( & USART0Queue, data );
}

int 
USART0DeQueue( )
{
	return deQueue( & USART0Queue );
}

ISR(USART0_RX_vect) 
{

  	uint8_t data = UDR0;
	int result;   
	
  	result = USART0EnQueue( data );
  	if ( result < 0 )
	{
		// Error code goes here
	}	
}

#endif /* USE_USART0 */

#if defined(USE_USART1)

void initUSART1(void) {

	initQueue( & USART1Queue );

	#undef BAUD
	#define BAUD USART1_BAUD
	#include <util/setbaud.h>

	// baud rate
	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;

	// double usart transmission speed
	#if USE_2X
		UCSR1A = (1 << U2X);
	#else
		UCSR1A = 0;
	#endif

	// rx complete interrupt
	// receiver
	// transmitter
	UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);

	// 8N1
	// asynchronous
	// parity disabled
	// 1 stop bit
	// character size 8 bit
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
} // initUSART1


void 
transmitBufferUSART1(uint8_t const buffer[], uint8_t buffer_length) 
{

	uint8_t x;

	for (x = 0; x < buffer_length; x++) {

		while ( !( UCSR1A & (1 << UDRE1) ) )
			asm volatile("nop"::);

		UDR1 = buffer[x];
	}
	while ( !( UCSR1A & (1 << TXC1) ) )
		asm volatile("nop"::);
} // transmitBufferUSART1

void 
transmitStringUSART1(char const * msg) 
{
    transmitBufferUSART1( (uint8_t *) msg, strlen(msg) );  
} // transmitStringUSART1


void 
transmitIntegerUSART1(int value, int radix) 
{
	char msg[17];
	itao(value, msg, radix);
    transmitStringUSART1( msg );  
} // transmitStringUSART1

int 
USART1EnQueue( uint8_t data )
{
	return enQueue( & USART1Queue, data );
}

int 
USART1DeQueue( )
{
	return deQueue( & USART1Queue );
}

ISR(USART1_RX_vect) 
{
//    static uint8_t count = 0;

  	uint8_t data = UDR1;
	int result;   
	char debug[16];

  	result = USART1EnQueue( data );
  	if ( result < 0 )
		{
			// Error code goes here
		}	
//    sprintf(debug,"IRQ: %3d\n",++count);
//    transmitStringUSART1( debug );
}

#endif /* USE_USART1 */
