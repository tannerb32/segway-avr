/*
 * buttons.h
 *
 * Created: 10/27/2011 1:51:36 PM
 *  Author: jacky
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <inttypes.h>

#if ROBOT == 3

#   define START_BUTTON_DDR			DDRD
#   define START_BUTTON_PORT		PORTD
#   define START_BUTTON_PIN         PIND
#   define START_BUTTON_BIT			0

#   define B1_BUTTON_DDR			DDRD
#   define B1_BUTTON_PORT			PORTD
#   define B1_BUTTON_PIN			PIND
#   define B1_BUTTON_BIT			1

#else
#   error "Undefined robot definition in buttons.h"
#endif

enum Buttons
{
	START_BUTTON = 1,
	BUTTON1 = 2
};

void initButtons();
uint8_t ButtonStart();
uint8_t Button1();

uint8_t Clicked(uint8_t (*button)(void));
#endif /* BUTTONS_H_ */