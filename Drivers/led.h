#ifndef __LED_H__
#define __LED_H__

#if defined(USE_LEDS)

#include <avr/io.h>

enum LED
{
	LED0,
	LED1,
	LED2,
	LED3,
	LED4
};

enum LED_STATE
{
	LED_ON,
	LED_OFF,
	LED_TOGGLE
};

#if ROBOT == 3
#   define LED0_DDR			DDRG
#   define LED0_PORT		PORTG
#   define LED0_BIT         0

#   define LED1_DDR			DDRG
#   define LED1_PORT		PORTG
#   define LED1_BIT         1

#   define LED2_DDR			DDRG
#   define LED2_PORT		PORTG
#   define LED2_BIT         2

#   define LED3_DDR			DDRG
#   define LED3_PORT		PORTG
#   define LED3_BIT         3

#   define LED4_DDR			DDRG
#   define LED4_PORT		PORTG
#   define LED4_BIT         4
#else
#   error "Unknown robot definition"
#endif

/* Prototypes */
void initLEDs( void );
void changeLED( enum LED led, enum LED_STATE state );

#if defined(TEST_LEDS)
void testTaskLEDs(void * arg);
#endif

#endif

#endif
