/**
 * Driver for the Touch sensors on the KAIST KRC kit.
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca> Tue Feb  6 02:25:32 CST 2007
 *
 */

#include <inttypes.h>
#include <avr/io.h>

#include "button_state.h"
#include "touch_driver.h"


void initTouchSubSystem(void)
{
    DDRF = DDRF & 0x00;         /* Set Bit 7,6 (buttons) and 5,4 (touch) as inputs */
    PORTF = PORTF & 0x00;       /* Turn off pull ups */
}

enum ButtonState getTouchSensor(enum TouchSensor touch)
{
    uint8_t result = Down;

    if ((touch == RunStop) && (TOUCH_PORT_IN & 0x40))
    {
        result = Up;
    }
    else if ((touch == Select) && (TOUCH_PORT_IN & 0x80))
    {
        result = Up;
    }
    else if ((touch == Touch1) && (TOUCH_PORT_IN & 0x10))
    {
        result = Up;
    }
    else if ((touch == Touch2) && (TOUCH_PORT_IN & 0x20))
    {
        result = Up;
    }

    return result;
}

