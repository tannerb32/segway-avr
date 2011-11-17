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
#	include "adc.h"
#endif /* USE_ADC */

#if defined(USE_TIMER_TICKS)
#	include "timer_ticks.h"
#endif /* USE_TIMER_TICKS */

#if defined(USE_USART0) || defined(USE_USART1)
#	include "serial.h"
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
#include "segway.h"

int main(void)
{
#if defined(USE_LEDS)
	initLEDs();
#endif

#if defined(USE_LEDS)
	changeLED(LED0,LED_ON);
	_delay_ms(100);
#endif

#if defined(USE_USART0)
	initUSART0();
#endif /* USE_USART0 */

#if defined(USE_USART1)
	initUSART1();
#endif /* USE_USART1 */

#if defined(USE_LEDS)
	changeLED(LED0,LED_OFF);
	changeLED(LED1,LED_ON);
	_delay_ms(100);
#endif

#if defined(USE_LCD)
	initLCDSubSystem();
#endif /* USE_LCD */
	
#if defined(USE_LEDS)
	changeLED(LED1,LED_OFF);
	changeLED(LED2,LED_ON);
	_delay_ms(100);
#endif

#if defined(USE_MOTOR)
	initMotorSubSystem();
#endif /* USE_MOTOR */

#if defined(USE_LEDS)
	changeLED(LED2,LED_OFF);
	changeLED(LED3,LED_ON);
	_delay_ms(100);
#endif

#if defined(USE_TIMER_TICKS)
	initTimerTicks( 16 );
#endif /* USE_TICKS_TIMER */

#if defined(USE_LEDS)
	changeLED(LED3,LED_OFF);
	changeLED(LED4,LED_ON);
	_delay_ms(100);
#endif

#if defined(USE_BUTTONS)
	initButtons();
#endif

#if defined(USE_SOUND)
	initSoundSubSystem();
#endif

	initRobot();

//	initContextTimer();

#if defined(USE_LEDS)
	changeLED(LED4,LED_OFF);
#endif

	sei();		
	
	clearLCD();
	printStringLCD(0,0,"Press Start");
	printStringLCD(1,0,"v");

	while(! Clicked(ButtonStart));

	clearLCD();

	//uint32_t current_time = 0;
	uint16_t angle;
	uint16_t light_l, light_r, light_m;
	uint16_t accel_x, accel_y, accel_z;

	char nl[] = "\n";
	char sp[] = " ";

	for(;;)
	{
		light_l = readADC(LIGHT_SENSOR_LEFT);
		light_r = readADC(LIGHT_SENSOR_RIGHT);
		light_m = readADC(LIGHT_SENSOR_MIDDLE);

		accel_x = readADC(ACCEL_X);
		accel_y = readADC(ACCEL_Y);
		accel_z = readADC(ACCEL_Z);

		printHexLCD(0, 0, accel_x);
		printHexLCD(0, 5, accel_y);
		printHexLCD(0, 10, accel_z);

		printHexLCD(1,0, light_l);
		printHexLCD(1,5, light_m);
		printHexLCD(1,10, light_r);

		//the following was for plotting sensor readings
		//printStringLCD(0,0, "10 bit ADC");

		//transmitIntegerUSART0(current_time, 10);
		//transmitStringUSART0(sp);
		//transmitIntegerUSART0(l, 10);
		//transmitStringUSART0(sp);
		//transmitIntegerUSART0(m, 10);
		//transmitStringUSART0(sp);
		//transmitIntegerUSART0(r, 10);
		//transmitStringUSART0(nl);
		//
		//_delay_ms(500);
		//current_time += 500;

		//setMotorSpeed(MotorLeft, 200);
		//setMotorSpeed(MotorRight, -200);
		//_delay_ms(100);
	
		//setMotorSpeed(MotorLeft, -200);
		//setMotorSpeed(MotorRight, +200);
		//_delay_ms(100);

		//setMotorSpeed(MotorLeft, 0);
		//setMotorSpeed(MotorRight, 0);
	}	

    return 0;
}

