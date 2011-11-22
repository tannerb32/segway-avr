/**
 * Driver for the DC motors of the KAIST KRC kit.
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca> Tue Feb  6 18:13:43 CST 2007
 *
 * The motors are controlled via
 */

#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#if defined(USE_MOTOR)

#include <inttypes.h>
#include <avr/io.h>

#include "robot.h"

enum
{
    MotorLeft = 0,
    MotorRight = 1,
    NUM_MOTORS = 2
};

#define MOTOR_MIN (0)

#define MOTOR_MAX (32768)

// Prototypes
/** Initialize the motor subsystem */
void initMotorSubSystem(void);

/** Set a motor speed */
void setMotorSpeed(uint8_t motor, int speed);

/** Stop the motor */
void stopMotor(uint8_t motor);

/** get current motor speed position */
int getMotor(uint8_t motor);

/* Private functions that should be used with care. They do NOT check the
 * Motor_lock semaphore first
 */
void _setMotorSpeed(uint8_t motor, int speed);

//
//  You should not need to modify anything below this line
//

/*
The motors are controlled via PWM channels. The AtMega128 has 2 8-bit PWM channels
and 6 channels with a programmable resolution of 2 to 16 bits.

The PWM channels are:
PWM=1: OC0/PB4
PWM=2: OC2/PB7 same as OC1C
PWM=3: OC1A/PB5
PWM=4: OC1B/PB6
PWM=5: OC1C/PB7 same as OC2
PWM=6: OC3A/PE3
PWM=7: OC3B/PE4
PWM=8: OC3C/PE5
*/

/* The following CPP process selects the correct data port, direction port, and mask */

#if   MOTOR_LEFT_PWM_MODE == 1
#   define MOTOR_PORT_LEFT                  PORTB
#   define MOTOR_PORT_LEFT_DIRECTION        DDRB
#   define MOTOR_PORT_LEFT_MASK             (1 << PB4)
#   define MOTOR_LEFT_PWM                   OCR0
#   if PRESCALAR_LEFT == 1
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 0 << CS01) | (1 << CS00) )
#   elif PRESCALAR_LEFT == 8
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 1 << CS01) | (0 << CS00) )
#   elif PRESCALAR_LEFT == 32
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 1 << CS01) | (1 << CS00) )
#   elif PRESCALAR_LEFT == 64
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 0 << CS01) | (0 << CS00) )
#   elif PRESCALAR_LEFT == 128
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 0 << CS01) | (1 << CS00) )
#   elif PRESCALAR_LEFT == 256
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 1 << CS01) | (0 << CS00) )
#   elif PRESCALAR_LEFT == 1024
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 1 << CS01) | (1 << CS00) )
#   else
#       error Unknown Timer 0 PRESCALAR value
#   endif
#elif MOTOR_LEFT_PWM_MODE == 2
#   define MOTOR_PORT_LEFT                  PORTB
#   define MOTOR_PORT_LEFT_DIRECTION        DDRB
#   define MOTOR_PORT_LEFT_MASK             (1 << PB7)
#   define MOTOR_LEFT_PWM                   OCR2
#   if PRESCALAR_LEFT == 1
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 0 << CS21) | (1 << CS20) )
#   elif PRESCALAR_LEFT == 8
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 1 << CS21) | (0 << CS20) )
#   elif PRESCALAR_LEFT == 64
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 1 << CS21) | (1 << CS20) )
#   elif PRESCALAR_LEFT == 256
#       define TIMER2_PRESCALAR_MASK        ( (1 << CS22) | ( 0 << CS21) | (0 << CS20) )
#   elif PRESCALAR_LEFT == 1024
#       define TIMER2_PRESCALAR_MASK        ( (1 << CS22) | ( 0 << CS21) | (1 << CS20) )
#   else
#       error Unknown Timer 2 PRESCALAR value
#   endif
#elif MOTOR_LEFT_PWM_MODE == 3
#   define MOTOR_PORT_LEFT                  PORTB
#   define MOTOR_PORT_LEFT_DIRECTION        DDRB
#   define MOTOR_PORT_LEFT_MASK             (1 << PB5)
#   define MOTOR_LEFT_PWM                   OCR1A
#elif MOTOR_LEFT_PWM_MODE == 4
#   define MOTOR_PORT_LEFT                  PORTB
#   define MOTOR_PORT_LEFT_DIRECTION        DDRB
#   define MOTOR_PORT_LEFT_MASK             (1 << PB6)
#   define MOTOR_LEFT_PWM                   OCR1B
#elif MOTOR_LEFT_PWM_MODE == 5
#   define MOTOR_PORT_LEFT                  PORTB
#   define MOTOR_PORT_LEFT_DIRECTION        DDRB
#   define MOTOR_PORT_LEFT_MASK             (1 << PB7)
#   define MOTOR_LEFT_PWM                   OCR1C
#elif MOTOR_LEFT_PWM_MODE == 6
#   define MOTOR_PORT_LEFT                  PORTE
#   define MOTOR_PORT_LEFT_DIRECTION        DDRE
#   define MOTOR_PORT_LEFT_MASK             (1 << PE3)
#   define MOTOR_LEFT_PWM                   OCR3A
#elif MOTOR_LEFT_PWM_MODE == 7
#   define MOTOR_PORT_LEFT                  PORTE
#   define MOTOR_PORT_LEFT_DIRECTION        DDRE
#   define MOTOR_PORT_LEFT_MASK             (1 << PE4)
#   define MOTOR_LEFT_PWM                   OCR3B
#elif MOTOR_LEFT_PWM_MODE == 8
#   define MOTOR_PORT_LEFT                  PORTE
#   define MOTOR_PORT_LEFT_DIRECTION        DDRE
#   define MOTOR_PORT_LEFT_MASK             (1 << PE5)
#   define MOTOR_LEFT_PWM                   OCR3C
#else
#   error "Unknown PWM_MODE Definition for left motor"
#endif /* MOTOR_LEFT_PWM_MODE */

#if   MOTOR_RIGHT_PWM_MODE == 1
#   define MOTOR_PORT_RIGHT                  PORTB
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRB
#   define MOTOR_PORT_RIGHT_MASK             (1 << PB4)
#   define MOTOR_RIGHT_PWM                   OCR0
#   if PRESCALAR_RIGHT == 1
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 0 << CS01) | (1 << CS00) )
#   elif PRESCALAR_RIGHT == 8
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 1 << CS01) | (0 << CS00) )
#   elif PRESCALAR_RIGHT == 32
#       define TIMER0_PRESCALAR_MASK        ( (0 << CS02) | ( 1 << CS01) | (1 << CS00) )
#   elif PRESCALAR_RIGHT == 64
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 0 << CS01) | (0 << CS00) )
#   elif PRESCALAR_RIGHT == 128
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 0 << CS01) | (1 << CS00) )
#   elif PRESCALAR_RIGHT == 256
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 1 << CS01) | (0 << CS00) )
#   elif PRESCALAR_RIGHT == 1024
#       define TIMER0_PRESCALAR_MASK        ( (1 << CS02) | ( 1 << CS01) | (1 << CS00) )
#   else
#       error Unknown Timer 0 PRESCALAR value
#   endif
#elif MOTOR_RIGHT_PWM_MODE == 2
#   define MOTOR_PORT_RIGHT                  PORTB
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRB
#   define MOTOR_PORT_RIGHT_MASK             (1 << PB7)
#   define MOTOR_RIGHT_PWM                   OCR2
#   if PRESCALAR_RIGHT == 1
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 0 << CS21) | (1 << CS20) )
#   elif PRESCALAR_RIGHT == 8
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 1 << CS21) | (0 << CS20) )
#   elif PRESCALAR_RIGHT == 64
#       define TIMER2_PRESCALAR_MASK        ( (0 << CS22) | ( 1 << CS21) | (1 << CS20) )
#   elif PRESCALAR_RIGHT == 256
#       define TIMER2_PRESCALAR_MASK        ( (1 << CS22) | ( 0 << CS21) | (0 << CS20) )
#   elif PRESCALAR_RIGHT == 1024
#       define TIMER2_PRESCALAR_MASK        ( (1 << CS22) | ( 0 << CS21) | (1 << CS20) )
#   else
#       error Unknown Timer 2 PRESCALAR value
#   endif
#elif MOTOR_RIGHT_PWM_MODE == 3
#   define MOTOR_PORT_RIGHT                  PORTB
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRB
#   define MOTOR_PORT_RIGHT_MASK             (1 << PB5)
#   define MOTOR_RIGHT_PWM                   OCR1A
#elif MOTOR_RIGHT_PWM_MODE == 4
#   define MOTOR_PORT_RIGHT                  PORTB
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRB
#   define MOTOR_PORT_RIGHT_MASK             (1 << PB6)
#   define MOTOR_RIGHT_PWM                   OCR1B
#elif MOTOR_RIGHT_PWM_MODE == 5
#   define MOTOR_PORT_RIGHT                  PORTB
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRB
#   define MOTOR_PORT_RIGHT_MASK             (1 << PB7)
#   define MOTOR_RIGHT_PWM                   OCR1C
#elif MOTOR_RIGHT_PWM_MODE == 6
#   define MOTOR_PORT_RIGHT                  PORTE
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRE
#   define MOTOR_PORT_RIGHT_MASK             (1 << PE3)
#   define MOTOR_RIGHT_PWM                   OCR3A
#elif MOTOR_RIGHT_PWM_MODE == 7
#   define MOTOR_PORT_RIGHT                  PORTE
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRE
#   define MOTOR_PORT_RIGHT_MASK             (1 << PE4)
#   define MOTOR_RIGHT_PWM                   OCR3B
#elif MOTOR_RIGHT_PWM_MODE == 8
#   define MOTOR_PORT_RIGHT                  PORTE
#   define MOTOR_PORT_RIGHT_DIRECTION        DDRE
#   define MOTOR_PORT_RIGHT_MASK             (1 << PE5)
#   define MOTOR_RIGHT_PWM                   OCR3C
#else
#   error "Unknown PWM_MODE Definition for right motor"
#endif /* MOTOR_RIGHT_PWM_MODE */

#endif /* USE_MOTOR */

#endif /* _MOTOR_DRIVER_H_ */
