#include "led.h"

#if defined(USE_LCD)
#   include "lcd_driver.h"
#endif

void 
initLEDs(void) 
{
	changeLED(LED0, LED_OFF);
	LED0_DDR = LED0_DDR | (1 << LED0_BIT );

	changeLED(LED1, LED_OFF);
	LED1_DDR = LED1_DDR | (1 << LED1_BIT );

	changeLED(LED2, LED_OFF);
	LED2_DDR = LED2_DDR | (1 << LED2_BIT );

	changeLED(LED3, LED_OFF);
	LED3_DDR = LED3_DDR | (1 << LED3_BIT );

	changeLED(LED4, LED_OFF);
	LED4_DDR = LED4_DDR | (1 << LED4_BIT );
} 

void
changeLED( enum LED led, enum LED_STATE state )
{
	if (led == LED0 )
	{
		if ( state == LED_OFF )
		{
			LED0_PORT = LED0_PORT | (1 << LED0_BIT );
		}
		else if ( state == LED_ON )
		{
			LED0_PORT = LED0_PORT & ( ~ (1 << LED0_BIT ) );			
		}
		else if ( state == LED_TOGGLE)
		{
			LED0_PORT = LED0_PORT ^ (1 << LED0_BIT );
		}
	}
	else if (led == LED1 )
	{
		if ( state == LED_OFF )
		{
			LED1_PORT = LED1_PORT | (1 << LED1_BIT );
		}
		else if ( state == LED_ON )
		{
			LED1_PORT = LED1_PORT & ( ~ (1 << LED1_BIT ) );			
		}
		else if ( state == LED_TOGGLE)
		{
			LED1_PORT = LED1_PORT ^ (1 << LED1_BIT );
		}		
	}
	else if (led == LED2 )
	{
		if ( state == LED_OFF )
		{
			LED2_PORT = LED2_PORT | (1 << LED2_BIT );
		}
		else if ( state == LED_ON )
		{
			LED2_PORT = LED2_PORT & ( ~ (1 << LED2_BIT ) );			
		}
		else if ( state == LED_TOGGLE)
		{
			LED2_PORT = LED2_PORT ^ (1 << LED2_BIT );
		}				
	}
	else if (led == LED3 )
	{
		if ( state == LED_OFF )
		{
			LED3_PORT = LED3_PORT | (1 << LED3_BIT );
		}
		else if ( state == LED_ON )
		{
			LED3_PORT = LED3_PORT & ( ~ (1 << LED3_BIT ) );			
		}
		else if ( state == LED_TOGGLE)
		{
			LED3_PORT = LED3_PORT ^ (1 << LED3_BIT );
		}		

	}
	else if (led == LED4 )
	{
		if ( state == LED_OFF )
		{
			LED4_PORT = LED4_PORT | (1 << LED4_BIT );
		}
		else if ( state == LED_ON )
		{
			LED4_PORT = LED4_PORT & ( ~ (1 << LED4_BIT ) );			
		}
		else if ( state == LED_TOGGLE)
		{
			LED4_PORT = LED4_PORT ^ (1 << LED4_BIT );
		}		
	}
}

#if defined(TEST_LEDS)
void
testTaskLEDs(void * arg )
{
	uint8_t i,j,k,l,m;
	
	for(;;)
	{
		for(i=0;i<2;i++)
		{
			if ( i != 0 )
			{
				changeLED(LED0, LED_ON);
			}
			else
			{
				changeLED(LED0, LED_OFF);								
			}
			for(j=0;j<2;j++)
			{
				if ( j != 0 )
				{
					changeLED(LED1, LED_ON);
				}
				else
				{
					changeLED(LED1, LED_OFF);								
				}
				for(k=0;k<2;k++)
				{
					if ( k != 0 )
					{
						changeLED(LED2, LED_ON);
					}
					else
					{
						changeLED(LED2, LED_OFF);								
					}
					for(l=0;l<2;l++)
					{
						if ( l != 0 )
						{
							changeLED(LED3, LED_ON);
						}
						else
						{
							changeLED(LED3, LED_OFF);								
						}
						for(m=0;m<2;m++)
						{
							if ( m != 0 )
							{
								changeLED(LED4, LED_ON);
							}
							else
							{
								changeLED(LED4, LED_OFF);								
							}
#if defined(USE_LCD)
							printHexByteLCD(0,0,i); printHexByteLCD(0,2,j); printHexByteLCD(0,4,k); printHexByteLCD(0,6,l); printHexByteLCD(0,8,m);
#endif
							sleep(100);
						}
					}
				}
			}
		}	
	}
}
#endif
    

