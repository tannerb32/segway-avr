#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

#define ADCMUX_MASK    ( (1 << MUX4 ) | ( 1 << MUX3 ) | (1 << MUX2 ) | (1 << MUX1 ) | (1 << MUX0 ) ) 

void initADC( );

uint8_t startADC(void);
void stopADC(void);

void addADC( uint8_t mask, uint8_t pullUp );
uint8_t delADC( uint8_t mask);

#if defined(HIGH_RES)
uint16_t readADC(uint8_t channel);
#else
uint8_t readADC(uint8_t channel);
#endif

#if defined(TEST_ADC)
void testTaskADC( void * arg );
#endif /* TEST_ADC */

#if defined(TEST_LIGHT_SENSORS)
void testTaskLightSensors( void * arg );
#endif /* TEST_ADC */
#endif
