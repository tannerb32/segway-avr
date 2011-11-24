#if defined(USE_LED)
#   include "led_driver.h"
#endif /* USE_LCD */

#if defined(USE_MOTOR)
#   include "motor_driver.h"
#endif /* USE_MOTOR */

#if defined(USE_TOUCH)
#   include "touch_driver.h"
#endif /* USE_TOUCH */

#if defined(USE_LCD)
#   include "lcd_driver.h"
#endif /* USE_LCD */

#if defined(USE_ADC)
#   include "adc.h"
#endif /* USE_ADC */

#if defined(USE_TIMER_TICKS)
#   include "timer_ticks.h"
#endif /* USE_TIMER_TICKS */

#if defined(USE_USART0) || defined(USE_USART1)
#   include "serial.h"
#endif /* defined(USE_USART0) || defined(USE_USART1) */

#if defined(USE_BUTTONS)
#   include "buttons.h"
#endif

#if defined(USE_LEDS)
#   include "led.h"
#endif

#if defined(USE_SOUND)
#   include "sound_driver.h"
#endif












#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "segway.h"
#include "pid.h"

#define RAD2DEG 57.2957796

void init_robot();

typedef enum
{
    RUN_MAIN,
    CALIBRATE,
    PLOT
} state;

int main(void)
{
    init_robot();

    //printStringLCD(0, 5, "Options");
    //_delay_ms(1200);
    //clearLCD();
    printStringLCD(0, 0, "Run");
    printStringLCD(1, 0, "v");
    //_delay_ms(1200);
    //clearLCD();
    //printStringLCD(0, 0, "Calibrate");
    //printStringLCD(1, 2, "v");
    //_delay_ms(1200);
    //clearLCD();

    uint32_t current_time = 0;
    //uint16_t angle;
    uint16_t light_l, light_r, light_m;
    uint32_t accel_x, accel_y, accel_z;

    char msg[64];

    while(!Clicked(ButtonStart));

    float alpha = 0.5f;
    uint32_t prev_accel_x = 0;
    uint32_t prev_accel_y = 0;
    uint32_t prev_accel_z = 0;

    struct accel ac;
    struct orient t;

    for (;;)
    {
        clearLCD();

        light_l = readADC(LIGHT_SENSOR_LEFT);
        light_r = readADC(LIGHT_SENSOR_RIGHT);
        light_m = readADC(LIGHT_SENSOR_MIDDLE);

        if(prev_accel_x == 0)
        {
            accel_x = readADC(ACCEL_X);
            accel_y = readADC(ACCEL_Y);
            accel_z = readADC(ACCEL_Z);
        }
        else
        {
            accel_x = (int64_t)prev_accel_x + alpha * ((int64_t)readADC(ACCEL_X) - prev_accel_x);
            accel_y = (int64_t)prev_accel_y + alpha * ((int64_t)readADC(ACCEL_Y) - prev_accel_y);
            accel_z = (int64_t)prev_accel_z + alpha * ((int64_t)readADC(ACCEL_Z) - prev_accel_z);
        }

        prev_accel_x = accel_x;
        prev_accel_y = accel_y;
        prev_accel_z = accel_z;

        update(accel_x, accel_y, accel_z);

        get_components(&ac);
        get_orient(&t); 

        //sprintf(msg, "L%u M%u R%u", light_l, light_m, light_r);

        //printIntegerLCD(0, 0,  prev_accel_x, 10);
        //printIntegerLCD(0, 5,  prev_accel_y, 10);
        //printIntegerLCD(0, 10, prev_accel_z, 10);

        //printStringLCD(0,0,msg);

        int32_t d1 = t.roll * RAD2DEG;
        int32_t d2 = ((t.roll * RAD2DEG) - d1) * 1000;

        sprintf(msg, "%ld.%03ld,", d1, d2); 
        transmitStringUSART0(msg);
        sprintf(msg, "\t%u,\t%u,\t%u\n", light_l, light_m, light_r); 
        transmitStringUSART0(msg);

        float ratio = 1.25f;
        int32_t speed = get_pid((float)(t.roll * RAD2DEG));

        printIntegerLCD(0, 0, speed, 10);
        printIntegerLCD(1, 0, d1, 10);
        setMotorSpeed(MotorLeft, speed);
        setMotorSpeed(MotorRight, speed * ratio);

        _delay_ms(20);
        //setMotorSpeed(MotorLeft, -200);
        //setMotorSpeed(MotorRight, +200);
        //_delay_ms(100);
        //setMotorSpeed(MotorLeft, 0);
        //setMotorSpeed(MotorRight, 0);
    }

    return 0;
}

void init_robot()
{
#if defined(USE_LEDS)
    initLEDs();
#endif
#if defined(USE_LEDS)
    changeLED(LED0, LED_ON);
    _delay_ms(100);
#endif
#if defined(USE_USART0)
    initUSART0();
#endif /* USE_USART0 */
#if defined(USE_USART1)
    initUSART1();
#endif /* USE_USART1 */
#if defined(USE_LEDS)
    changeLED(LED0, LED_OFF);
    changeLED(LED1, LED_ON);
    _delay_ms(100);
#endif
#if defined(USE_LCD)
    initLCDSubSystem();
#endif /* USE_LCD */
#if defined(USE_LEDS)
    changeLED(LED1, LED_OFF);
    changeLED(LED2, LED_ON);
    _delay_ms(100);
#endif
#if defined(USE_MOTOR)
    initMotorSubSystem();
#endif /* USE_MOTOR */
#if defined(USE_LEDS)
    changeLED(LED2, LED_OFF);
    changeLED(LED3, LED_ON);
    _delay_ms(100);
#endif
#if defined(USE_TIMER_TICKS)
    initTimerTicks(16);
#endif /* USE_TICKS_TIMER */
#if defined(USE_LEDS)
    changeLED(LED3, LED_OFF);
    changeLED(LED4, LED_ON);
    _delay_ms(100);
#endif
#if defined(USE_BUTTONS)
    initButtons();
#endif
#if defined(USE_SOUND)
    initSoundSubSystem();
#endif
    initRobot();
    //  initContextTimer();
#if defined(USE_LEDS)
    changeLED(LED4, LED_OFF);
#endif
    sei();
    clearLCD();
}
