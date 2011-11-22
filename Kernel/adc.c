#include <avr/io.h>
#include <avr/interrupt.h>

#include "led.h"

#if defined(USE_ADC)
#   include "adc.h"
#endif /* USE_ADC */

#if defined(TEST_ADC) || defined(TEST_LIGHT_SENSORS)
#   include "lcd_driver.h"
#endif /* TEST_ADC */

#include "robot.h"

#if defined(HIGH_RES)
static uint16_t adc_values[8];
#else
static uint8_t adc_values[8];
#endif

static uint8_t adc_mask;
static uint8_t pIndex = 0;
static uint8_t ppIndex = 0;


/*
 * initADC: initialize the AD converter.
 * The mask input has a 1 for every bit that should be checked
 */

void initADC()
{
    // ADC enable
    // ADC start conversion
    // ADC free running mode
    // set prescalar 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // ADC0
#if defined(HIGH_RES)
    ADMUX = (1 << REFS0);
#else
    ADMUX = (1 << REFS0) | (1 << ADLAR);
#endif
    ADMUX = (ADMUX & (~ ADCMUX_MASK));
    adc_mask = 0;
}

void addADC(uint8_t mask, uint8_t pullUp)
{
    /* Select input for the bits in the mask */
    DDRF = DDRF & (~ mask);

    if (pullUp)
    {
        /* Enable pull-up */
        PORTF = PORTF | (mask);
    }
    else
    {
        PORTF = PORTF & (~ mask);
    }

    adc_mask = adc_mask | mask;
}

uint8_t delADC(uint8_t mask)
{
    uint8_t tmp;
    uint8_t result = 0;
    tmp = adc_mask & (~ mask);

    if (tmp != 0)
    {
        PORTF = PORTF & (~mask);
        adc_mask = tmp;
    }
    else
    {
        result = 1;
    }

    return result;
}

void stopADC()
{
    ADCSRA = ADCSRA & ~((1 << ADIE) | (1 << ADFR));
}

uint8_t startADC()
{
    uint8_t result;

    if (adc_mask != 0)
    {
        ADCSRA = ADCSRA | (1 << ADIE) | (1 << ADFR) | (1 << ADSC);
        result = 0;
    }
    else
    {
        result = 1;
    }

    return result;
}

#if defined(HIGH_RES)
uint16_t readADC(uint8_t channel)
{
    return adc_values[ channel & 0x07];
}
#else
uint8_t readADC(uint8_t channel)
{
    return adc_values[ channel & 0x07];
}
#endif

ISR(ADC_vect)
{
    uint8_t nIndex;
    uint8_t tmp;
#if defined(HIGH_RES)
    adc_values[ppIndex] = ADCW;
#else
    adc_values[ppIndex] = ADCH;
#endif
    nIndex = (pIndex + 1) & 0x07;

    while (((1 << nIndex) & adc_mask) == 0)
    {
        nIndex = (nIndex + 1) & 0x07;
    }

    tmp = ADMUX & (~ADCMUX_MASK);
    ADMUX = tmp | nIndex;
    ppIndex = pIndex;
    pIndex = nIndex;
}

