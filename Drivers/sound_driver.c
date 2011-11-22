/*
 * sound_driver.c
 *
 * Created: 11/2/2011 3:27:22 PM
 *  Author: jacky
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <util/delay.h>

#include "sound_driver.h"

void initSoundSubSystem(void)
{
    /* Setup the bits for the sound port */
    SOUND_PORT_DIRECTION = SOUND_PORT_DIRECTION | SOUND_PORT_MASK;
    SOUND_PORT = (SOUND_PORT & (~SOUND_PORT_MASK));   // Turn speaker off? *** Must check if it is true or inverted
#if ( SOUND_MODE == 3 ) || (SOUND_MODE == 4) || (SOUND_MODE == 5)
    TCNT1 = 0; /* Reset Timer 1 */
    TCCR1A = (0x02 << COM1A0) | (0x00 << COM1B0) | (0x00 << COM1C0) | (0x00 << WGM10); /* Enable phase correct PWM mode,  */
    TCCR1B = (0x02 << WGM12) | (0x01 << CS10);  /* Setup Phase and Frequency correct PWM mode, prescalar = 1 */
#warning "Add FOC and Prescalar mask for timer 1"
#elif ( SOUND_MODE == 6 ) || ( SOUND_MODE == 7 ) || ( SOUND_MODE == 8 )
    TCNT3 = 0; /* Reset timer 3 counter */
    TCCR3A = (0x02 << COM3A0) | (0x00 << COM3B0) | (0x00 << WGM30); /* Enable phase and frequency correct PWM mode,  */
    TCCR3B = (0x02 << WGM32) | (0x01 << CS30);  /* Setup Fast PWM mode, prescalar = 1 */
#warning Implement selection of FOC channel and PRESCALAR mask
#endif /* Using Timer 3 */
    SOUND_VOLUME = 0;
}

