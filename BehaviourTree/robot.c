//-----------------------------------------
// PROJECT: SoccerBot
// AUTHOR : Stela H. Seo <shb8775@hotmail.com>
//-----------------------------------------

//----------------------------------------------------------------------------
// INCLUDE HEADERS
//----------------------------------------------------------------------------
#include <stdint.h>

#include "robot.h"

#if defined(USE_MOTOR)
#   include "motor_driver.h"
#endif /* USE_MOTOR */

#if defined(USE_USART0) || defined(USE_USART1)
#   include "serial.h"
#endif /* defined(USE_USART0) || defined(USE_USART1) */

#if defined(USE_ADC) || defined(USE_LIGHT_SENSORS)
#   include "adc.h"
#endif

#if defined(USE_LIGHT_SENSORS)
#include <stdio.h>
#include "lcd_driver.h"
#endif

//----------------------------------------------------------------------------
// CONSTANTS / TYPES
//----------------------------------------------------------------------------
#define MAX_COMPASS     1
#define MAX_IR          8
#define MAX_LIGHT       4
#define MAX_SONAR       3
#define MAX_SENSORS     (MAX_COMPASS + MAX_IR + MAX_LIGHT + MAX_SONAR)
#define MAX_FUNCTION    2
#define COMPASS_FACING_DIRECTION        0
#define COMPASS_STRIKE_DIRECTION        1
#define INFRARED_ANGLE_TO_BALL          0
#define INFRARED_DISTANCE_TO_BALL       1
#define LIGHT_DETECT_LIGHT              0
#define LIGHT_DETECT_DARK               1
#define SONAR_DISTANCE_TO_LEFT_WALL     0
#define SONAR_DISTANCE_TO_RIGHT_WALL    1

//----------------------------------------------------------------------------
// FUNCTIONS / METHODS
//----------------------------------------------------------------------------
void robotForward(int16_t power)
{
    setMotorSpeed(MotorLeft, power * LEFT_MOTOR_GAIN);
    setMotorSpeed(MotorRight, power * RIGHT_MOTOR_GAIN);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor enum CommandDefinitions */
    transmitStringUSART0("MC\x01\n");
#endif
}

void robotBackward(int16_t power)
{
    setMotorSpeed(MotorLeft, - power * LEFT_MOTOR_GAIN);
    setMotorSpeed(MotorRight, - power * RIGHT_MOTOR_GAIN);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x02\n");
#endif
}


void robotTurnLeft(int16_t power)
{
    setMotorSpeed(MotorLeft, 0);
    setMotorSpeed(MotorRight, power * RIGHT_MOTOR_GAIN);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x03\n");
#endif
}

void robotTurnRight(int16_t power)
{
    setMotorSpeed(MotorLeft, power * LEFT_MOTOR_GAIN);
    setMotorSpeed(MotorRight, 0);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x04\n");
#endif
}

void robotSpinLeft(int16_t power)
{
    setMotorSpeed(MotorLeft, -power * LEFT_MOTOR_GAIN);
    setMotorSpeed(MotorRight, power * RIGHT_MOTOR_GAIN);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x05\n");
#endif
}

void robotSpinRight(int16_t power)
{
    setMotorSpeed(MotorLeft, power * LEFT_MOTOR_GAIN);
    setMotorSpeed(MotorRight, -power * RIGHT_MOTOR_GAIN);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x06\n");
#endif
}


void robotBrake(int16_t power)
{
    setMotorSpeed(MotorLeft, 0);
    setMotorSpeed(MotorRight, 0);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x07\n");
#endif
}


void robotStop(void)
{
    setMotorSpeed(MotorLeft, 0);
    setMotorSpeed(MotorRight, 0);
#if defined(USE_MONITOR)
    /* Make sure these match the C# code in FormMonitor */
    transmitStringUSART0("MC\x08\n");
#endif
}

void initRobot()
{
    initADC();
    addADC(LIGHT_SENSORS_MASK, 0);
    addADC(ACCEL_MASK, 0);
    startADC();
}

