/*
 * buttons.c
 *
 * Created: 10/27/2011 1:51:17 PM
 *  Author: jacky
 */


#if defined(USE_BUTTONS)

#include <avr/io.h>

#include "buttons.h"

#if defined(USE_LCD)
#   include "lcd_driver.h"
#endif

void initButtons()
{
    START_BUTTON_DDR = (START_BUTTON_DDR & (~(1 << START_BUTTON_BIT)));       // Set direction of port to input
    START_BUTTON_PORT = (START_BUTTON_PORT) | (1 << START_BUTTON_BIT);            // Enable pull-up resistor
    B1_BUTTON_DDR = (B1_BUTTON_DDR & (~(1 << B1_BUTTON_BIT)));        // Set direction of port to input
    B1_BUTTON_PORT = (B1_BUTTON_PORT) | (1 << B1_BUTTON_BIT);         // Enable pull-up resistor
}

uint8_t Clicked(uint8_t (* button)())
{
    while (button())
    {
        asm volatile("nop"::);
    }

    while (! button())
    {
        asm volatile("nop"::);
    }

    return 1;
}

uint8_t ButtonStart()
{
    return !(START_BUTTON_PIN & (1 << START_BUTTON_BIT));
}

uint8_t Button1()
{
    return !(B1_BUTTON_PIN & (1 << B1_BUTTON_BIT));
}

#if defined(TEST_BUTTONS)
void testTaskButtons(void *arg)
{
    uint8_t start;
    uint8_t b1;

    for (;;)
    {
        start = ButtonStart();
        b1 = Button1();
#if defined(USE_LCD)
        printStringLCD(1, 0, "Start:");
        printHexByteLCD(1, 6, start);
        printStringLCD(1, 10, "B1:");
        printHexByteLCD(1, 13, b1);
#endif
        sleep(30);
    }
}
#endif
#endif

