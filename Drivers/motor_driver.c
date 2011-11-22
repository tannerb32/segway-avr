/**
 * Driver for the DC motors of the NKFUST SoccerBot kit
 *
 *
 * The motors are connected to PortB 6,7 and 4,5
 *
 */

#include <inttypes.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#if defined(USE_LCD)
#   include "lcd_driver.h"
#endif /* USE_LCD */

#if defined(TEST_MOTOR_H_BRIDGE)
#   include <util/delay.h>
#endif /* TEST_MOTOR_H_BRIDGE */

#include "motor_driver.h"

volatile int motorSettings[ NUM_MOTORS ] =
{
    0x00,
    0x00
};

//static uint16_t clamp( uint16_t min, uint16_t val, uint16_t max );

/** Initialize the DC motor subsystem.
  Switch PORTD[ 7,6 ] and [ 5,4 ] to output
  Setup 8 bit PWM on Timer 3
  */

void initMotorSubSystem(void)

{
    uint8_t i;
    /* Setup the bits for the left H bridge as output and stop motor */
    MOTOR_LEFT_H_BRIDGE_PORT_DIRECTION = MOTOR_LEFT_H_BRIDGE_PORT_DIRECTION | MOTOR_LEFT_H_BRIDGE_PORT_MASK;
    MOTOR_LEFT_H_BRIDGE_PORT = (MOTOR_LEFT_H_BRIDGE_PORT & (~MOTOR_LEFT_H_BRIDGE_PORT_MASK)) | MOTOR_LEFT_H_BRIDGE_STOP_VALUE;
    /* Setup the bits for the right H bridge as output and stop motor */
    MOTOR_RIGHT_H_BRIDGE_PORT_DIRECTION = MOTOR_RIGHT_H_BRIDGE_PORT_DIRECTION | MOTOR_RIGHT_H_BRIDGE_PORT_MASK;
    MOTOR_RIGHT_H_BRIDGE_PORT = (MOTOR_RIGHT_H_BRIDGE_PORT & (~MOTOR_RIGHT_H_BRIDGE_PORT_MASK)) | MOTOR_RIGHT_H_BRIDGE_STOP_VALUE;
#if ( MOTOR_LEFT_PWM_MODE == 1 ) || ( MOTOR_RIGHT_PWM_MODE == 1 )
    TCNT0 = 0;
    /* TCCR0 definitions */
    /* FOC0 is not used in PWM modes */
    /* WGM01:WGM00 = 0:1 selects phase correct PWM mode */
    /* COM01:COM00 = 0:1 sets output pin to 0 after match */
    /* CS02:CS00 = 1:1:1 selects 1024 pre-scalar */
    /* CS02:CS00 = 1:0:0 selects 64 pre-scalar */
    TCCR0 = (0 << FOC0) | (0 << WGM01) | (1 << COM01) | (0 << COM00) | (1 << WGM00) | TIMER0_PRESCALAR_MASK;
    //ASSR = ASSR & ~ (1 << AS0);
    /* TIMSK = */
#endif /* Using Timer 0 */
#if ( MOTOR_LEFT_PWM_MODE == 2 ) || ( MOTOR_RIGHT_PWM_MODE == 2 )
    TCNT2 = 0;
    /* TCCR2 definitions */
    /* FOC0 is not used in PWM modes */
    /* WGM21:WGM20 = 0:1 selects phase correct PWM mode */
    /* COM21:COM20 = 0:1 sets output pin to 0 after match */
    TCCR2 = (0 << FOC2) | (1 << COM21) | (0 << COM20) | (0 << WGM21) | (1 << WGM20) | TIMER2_PRESCALAR_MASK;
    /* TIMSK */
#endif /* Using Timer 2 */
#if ( MOTOR_LEFT_PWM_MODE == 3 ) || ( MOTOR_RIGHT_PWM_MODE == 3 ) || ( MOTOR_LEFT_PWM_MODE == 4 ) || ( MOTOR_RIGHT_PWM_MODE == 4 ) || ( MOTOR_LEFT_PWM_MODE == 5 ) || ( MOTOR_RIGHT_PWM_MODE == 5 )
    TCNT1 = 0; /* Reset Timer 1 */
    TCCR1A = (0x02 << COM1A0) | (0x02 << COM1B0) | (0x03 << WGM10); /* Enable phase correct PWM mode, 10 bits, Set on compare */
    TCCR1B = (0x00 << WGM12) | (0x04 << CS10);  /* Setup Phase correct PWM mode, 10 bit */
    TCCR1C = (0 << FOC1A) | (0 << FOC1B);     /* Enable OC output for channel A and B */
#warning "Add FOC and Prescalar mask for timer 1"
#endif /* Using Timer 1 */
#if ( MOTOR_LEFT_PWM_MODE == 6 ) || ( MOTOR_RIGHT_PWM_MODE == 6 ) || ( MOTOR_LEFT_PWM_MODE == 7 ) || ( MOTOR_RIGHT_PWM_MODE == 7 ) || ( MOTOR_LEFT_PWM_MODE == 8 ) || ( MOTOR_RIGHT_PWM_MODE == 8 )
    TCNT3 = 0; /* Reset timer 3 counter */
    TCCR3A = (0x02 << COM3A0) | (0x02 << COM3B0) | (0x03 << WGM30); /* 0xA3 Enable Fast PWM mode, 10 bits, Set on compare */
    TCCR3B = (0x01 << WGM32) | (0x04 << CS30);  /* Setup Fast PWM mode, 10 bit */
    TCCR3C = (0 << FOC3A) | (0 << FOC3B);     /* Enable OC output for channel A and B */
#error Implement selection of FOC channel and PRESCALAR mask
#endif /* Using Timer 3 */
    /* Setup the OC pin as output and clear it */
    MOTOR_PORT_LEFT_DIRECTION = MOTOR_PORT_LEFT_DIRECTION | MOTOR_PORT_LEFT_MASK;
    MOTOR_PORT_LEFT = (MOTOR_PORT_LEFT & (~ MOTOR_PORT_LEFT_MASK));
    MOTOR_PORT_RIGHT_DIRECTION = MOTOR_PORT_RIGHT_DIRECTION | MOTOR_PORT_RIGHT_MASK;
    MOTOR_PORT_RIGHT = (MOTOR_PORT_RIGHT & (~ MOTOR_PORT_RIGHT_MASK));

    for (i = 0; i < NUM_MOTORS; i++)
    {
        motorSettings[ i ] = 0;
    }

    MOTOR_RIGHT_PWM = 0;
    MOTOR_LEFT_PWM = 0;
}

void setMotorSpeed(uint8_t motor, int speed)
{
    uint16_t t_speed;
    uint8_t mask;

    if (/* ( motor >= 0 ) && */ (motor < NUM_MOTORS))
    {
        speed = speed /* * MOTOR_GAIN */;

        /*
           if ( motor == MotorLeft)
           {
           speed = - speed;
           }
           */
        if (speed >= 0)
        {
            t_speed = speed;
        }
        else
        {
            t_speed = -speed;
        }

        if (motor == MotorRight)
        {
            if (speed > 0)
            {
                mask = MOTOR_RIGHT_H_BRIDGE_FORWARD_VALUE;
            }
            else if (speed < 0)
            {
                mask = MOTOR_RIGHT_H_BRIDGE_BACKWARD_VALUE;
            }
            else
            {
                mask = MOTOR_RIGHT_H_BRIDGE_STOP_VALUE;
            }

            MOTOR_RIGHT_H_BRIDGE_PORT = (MOTOR_RIGHT_H_BRIDGE_PORT & ~ MOTOR_RIGHT_H_BRIDGE_PORT_MASK) | mask;
            MOTOR_RIGHT_PWM = t_speed;
        }
        else if (motor == MotorLeft)
        {
            if (speed > 0)
            {
                mask = MOTOR_LEFT_H_BRIDGE_FORWARD_VALUE;
            }
            else if (speed < 0)
            {
                mask = MOTOR_LEFT_H_BRIDGE_BACKWARD_VALUE;
            }
            else
            {
                mask = MOTOR_LEFT_H_BRIDGE_STOP_VALUE;
            }

            MOTOR_LEFT_H_BRIDGE_PORT = (MOTOR_LEFT_H_BRIDGE_PORT & ~ MOTOR_LEFT_H_BRIDGE_PORT_MASK) | mask;
            MOTOR_LEFT_PWM = t_speed;
        }

        motorSettings[ motor ] = speed;
    }
}

int getMotor(uint8_t motor)
{
    int8_t ret = 0;

    if (/* ( motor >= 0 ) && */ (motor < NUM_MOTORS))
    {
        ret = motorSettings[ motor ];
    }

    return ret;
}

void stopMotor(uint8_t motor)
{
    setMotorSpeed(motor, 0);
}
