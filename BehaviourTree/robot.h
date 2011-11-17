//-----------------------------------------
// PROJECT: SoccerBot
// AUTHOR : Jacky Baltes <jacky@taibotics.com>
// 
//-----------------------------------------

//----------------------------------------------------------------------------
// DEFINE HEADER
//----------------------------------------------------------------------------
#ifndef ROBOT_H
#define ROBOT_H


//----------------------------------------------------------------------------
// INCLUDE HEADERS
//----------------------------------------------------------------------------
#include <stdint.h>


//----------------------------------------------------------------------------
// EXTERN C
//----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------------
// CONSTANTS / TYPES
//----------------------------------------------------------------------------

#if ROBOT == 1

#   if defined(USE_MOTOR)
/* The following defines are for the original educational robot version 1 */

/** Output compare register for motor A */
#define MOTOR_LEFT_PWM_MODE     7

/** Output compare register for motor B */
#define MOTOR_RIGHT_PWM_MODE    6

#define MOTOR_LEFT_H_BRIDGE_PORT	        PORTB
#define MOTOR_LEFT_H_BRIDGE_PORT_DIRECTION  DDRB
#define MOTOR_LEFT_H_BRIDGE_PORT_MASK       ( (uint8_t)  ( ( 1 << PB5) | (1 << PB6 ) ) )
#define MOTOR_LEFT_H_BRIDGE_FORWARD_VALUE
#define MOTOR_LEFT_H_BRIDGE_BACKWARD_VALUE
#define MOTOR_LEFT_H_BRIDGE_STOP_VALUE

#define MOTOR_RIGHT_H_BRIDGE_PORT	        PORTB
#define MOTOR_RIGHT_H_BRIDGE_PORT_DIRECTION  DDRB
#define MOTOR_RIGHT_H_BRIDGE_PORT_MASK       ( (uint8_t) ( ( 1 << PB3) | (1 << PB2 ) ) )
#define MOTOR_RIGHT_H_BRIDGE_FORWARD_VALUE
#define MOTOR_RIGHT_H_BRIDGE_BACKWARD_VALUE
#define MOTOR_RIGHT_H_BRIDGE_STOP_VALUE
#endif /* USE_MOTOR */

#if defined(USE_LIGHT_SENSORS)
# error Light sensors not implemented yet
#endif /* USE_LIGHT_SENSORS */

#elif ROBOT == 2
/******************************************************************************/
/* Defintions for version 2 of the educational robot kit                      */
/******************************************************************************/

/* The following defines are for the 2nd Version of the Educational Robot Kit */

#   if defined(USE_MOTOR)
/** PWM Mode for left motor */
#define MOTOR_LEFT_PWM_MODE     2

/** PWM Mode for right motor */
#define MOTOR_RIGHT_PWM_MODE    1

/* Possible pre scalar values 1(Does not work right now), 8, 32, 64, 256, 1024 */
/* Should be the same for both channels */
#define PRESCALAR_LEFT		64
#define PRESCALAR_RIGHT		64

#define MOTOR_LEFT_H_BRIDGE_PORT				PORTB
#define MOTOR_LEFT_H_BRIDGE_PORT_DIRECTION		DDRB
#define MOTOR_LEFT_H_BRIDGE_PORT_MASK			( ( uint8_t ) ( ( 1 << PB5) | (1 << PB6 ) ) )

/* These depend on the hardware for the H bridge */
#define MOTOR_LEFT_H_BRIDGE_FORWARD_VALUE		( ( uint8_t ) ( ( 1 << PB5) | (0 << PB6 ) ) )
#define MOTOR_LEFT_H_BRIDGE_BACKWARD_VALUE		( ( uint8_t ) ( ( 0 << PB5) | (1 << PB6 ) ) )
#define MOTOR_LEFT_H_BRIDGE_STOP_VALUE			( ( uint8_t ) ( ( 0 << PB5) | (0 << PB6 ) ) )

#define MOTOR_RIGHT_H_BRIDGE_PORT				PORTB
#define MOTOR_RIGHT_H_BRIDGE_PORT_DIRECTION		DDRB
#define MOTOR_RIGHT_H_BRIDGE_PORT_MASK			( ( uint8_t ) ( ( 1 << PB2) | (1 << PB3 ) ) ) 

/* These depend on the hardware of the H bridge */
#define MOTOR_RIGHT_H_BRIDGE_FORWARD_VALUE		( ( uint8_t ) ( ( 1 << PB2) | (0 << PB3 ) ) )
#define MOTOR_RIGHT_H_BRIDGE_BACKWARD_VALUE		( ( uint8_t ) ( ( 0 << PB2) | (1 << PB3 ) ) )
#define MOTOR_RIGHT_H_BRIDGE_STOP_VALUE			( ( uint8_t ) ( ( 0 << PB2) | (0 << PB3 ) ) )
#endif /* USE_MOTOR */

#if defined(USE_ACCELEROMETER)
#   define ACCEL_X                                 5
#   define ACCEL_Y                                 6
#   define ACCEL_Z                                 7
#   define ACCEL_MASK                              ((uint8_t) ((1<<ACCEL_X) | (1<<ACCEL_Y) | (1 << ACCEL_Z)))
#endif /* USE_ACCELEROMETER */

#if defined(USE_LIGHT_SENSORS)
#   define LIGHT_SENSOR_LEFT                       1
#   define LIGHT_SENSOR_MIDDLE                     2
#   define LIGHT_SENSOR_RIGHT                      3
#   define LIGHT_SENSORS_MASK                      ((uint8_t) ((1<<LIGHT_SENSOR_LEFT) | (1<<LIGHT_SENSOR_MIDDLE) | (1 << LIGHT_SENSOR_RIGHT)))


extern int16_t __snsvalue_9_0;
extern int16_t __snsvalue_9_1;
extern int16_t __snsvalue_10_0;
extern int16_t __snsvalue_10_1;
extern int16_t __snsvalue_11_0;
extern int16_t __snsvalue_11_1;
#   endif /* USE_LIGHT_SENSORS */
#elif ROBOT == 3
/******************************************************************************/
/* Defintions for version 3 of the educational robot kit                      */
/******************************************************************************/

#   if defined(USE_MOTOR)
/** PWM Mode for right motor */
#define MOTOR_RIGHT_PWM_MODE    4
/** PWM Mode for left motor */
#define MOTOR_LEFT_PWM_MODE     3

/* Possible pre scalar values 1(Does not work right now), 8, 32, 64, 256, 1024 */
/* Should be the same for both channels */
#define PRESCALAR_LEFT		64
#define PRESCALAR_RIGHT		64

#define MOTOR_RIGHT_H_BRIDGE_PORT				PORTB
#define MOTOR_RIGHT_H_BRIDGE_PORT_DIRECTION		DDRB
#define MOTOR_RIGHT_H_BRIDGE_PORT_MASK			( ( uint8_t ) ( ( 1 << PB2) | (1 << PB3 ) ) )

/* These depend on the hardware for the H bridge */
#define MOTOR_RIGHT_H_BRIDGE_FORWARD_VALUE		( ( uint8_t ) ( ( 0 << PB2) | (1 << PB3 ) ) ) 
#define MOTOR_RIGHT_H_BRIDGE_BACKWARD_VALUE		( ( uint8_t ) ( ( 1 << PB2) | (0 << PB3 ) ) ) 
#define MOTOR_RIGHT_H_BRIDGE_STOP_VALUE			( ( uint8_t ) ( ( 0 << PB2) | (0 << PB3 ) ) )

#define MOTOR_LEFT_H_BRIDGE_PORT				PORTB
#define MOTOR_LEFT_H_BRIDGE_PORT_DIRECTION		DDRB
#define MOTOR_LEFT_H_BRIDGE_PORT_MASK			( ( uint8_t ) ( ( 1 << PB0) | (1 << PB1 )))

/* These depend on the hardware of the H bridge */
#define MOTOR_LEFT_H_BRIDGE_FORWARD_VALUE		( ( uint8_t ) ( ( 0 << PB0) | (1 << PB1 )))
#define MOTOR_LEFT_H_BRIDGE_BACKWARD_VALUE		( ( uint8_t ) ( ( 1 << PB0) | (0 << PB1 )))
#define MOTOR_LEFT_H_BRIDGE_STOP_VALUE			( ( uint8_t ) ( ( 0 << PB0) | (0 << PB1 )))
#endif /* USE_MOTOR */

#if defined(USE_ACCELEROMETER)
#   define ACCEL_X                                 5
#   define ACCEL_Y                                 6
#   define ACCEL_Z                                 7
#   define ACCEL_MASK                              ((uint8_t) ((1<<ACCEL_X) | (1<<ACCEL_Y) | (1 << ACCEL_Z)))
#endif /* USE_ACCELEROMETER */

#if defined(USE_LIGHT_SENSORS)
#   define LIGHT_SENSOR_LEFT                       1
#   define LIGHT_SENSOR_MIDDLE                     2
#   define LIGHT_SENSOR_RIGHT                      3
#   define LIGHT_SENSORS_MASK                      ( ( uint8_t ) ( (1<<LIGHT_SENSOR_LEFT) | (1<<LIGHT_SENSOR_MIDDLE) | (1 << LIGHT_SENSOR_RIGHT) ) )

extern int16_t __snsvalue_9_0;
extern int16_t __snsvalue_9_1;
extern int16_t __snsvalue_10_0;
extern int16_t __snsvalue_10_1;
extern int16_t __snsvalue_11_0;
extern int16_t __snsvalue_11_1;
#   endif /* USE_LIGHT_SENSORS */
#else
#	error "Unknown robot definition"
#endif /* ROBOT */

//----------------------------------------------------------------------------
// PROTOTYPES
//----------------------------------------------------------------------------

void initRobot();

void robotForward( int16_t power );
void robotBackward( int16_t power );
void robotTurnLeft( int16_t power );
void robotTurnRight( int16_t power );
void robotSpinLeft( int16_t power );
void robotSpinRight( int16_t power );
void robotBrake( int16_t power );
void robotStop( void );
void updateSensor( void );

//----------------------------------------------------------------------------
// END OF EXTERN C
//----------------------------------------------------------------------------
#ifdef __cplusplus
} // end extern "C"
#endif

//----------------------------------------------------------------------------
// END OF DEFINE HEADER
//----------------------------------------------------------------------------
#endif
