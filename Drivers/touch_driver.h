/**
 * Driver for the Touch sensors on the KAIST KRC kit. 
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca> Tue Feb  6 02:25:32 CST 2007
 *
 */

#ifndef _TOUCH_DRIVER_H_
#define _TOUCH_DRIVER_H_

#include "button_state.h"

#define TOUCH_PORT_IN PORTC
#define TOUCH_PORT_DIRECTION DDRC

enum TouchSensor
  {
    RunStop = 0,
    Select = 1,
    Touch1 = 2,
    Touch2 = 3,
    NUM_TOUCH_SENSORS
  };

/** Initialize the touch sensor subsystem */
void initTouchSubSystem( void );

/** read the raw button state */
enum ButtonState getTouchSensor( enum TouchSensor touch );

#endif /* _TOUCH_DRIVER_H_ */
