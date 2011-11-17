/**
 * Driver for the LCD of the NKFUST Robot
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca> 
 *
 */ 

#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include <inttypes.h>
#include "kernel.h"

#define LCD_DATA_PORT          PORTA
#define LCD_DATA_PORT_DIR      DDRA

#define LCD_CONTROL_PORT       PORTE 		
#define LCD_CONTROL_PORT_DIR   DDRE

#define LCD_WRITE_DATA_SETUP             (1 << PE5)
#define LCD_WRITE_CONTROL_SETUP          0

#define LCD_WRITE_DATA_SETUP_ENABLE      ( (1 << PE5) | ( 1 << PE7) )
#define LCD_WRITE_CONTROL_SETUP_ENABLE   (1 << PE7)

#define LCD_WRITE_DATA_DONE              (1 << PE5 )
#define LCD_WRITE_CONTROL_DONE           0

#define LCD_READ_DATA_SETUP              ( ( 1 << PE6) | (1 << PE5) )
#define LCD_READ_CONTROL_SETUP           (1 << PE6)

#define LCD_READ_DATA_SETUP_ENABLE       ( (1 << PE6) | (1 << PE5) | ( 1 << PE7) ) )
#define LCD_READ_CONTROL_SETUP_ENABLE    ( 1 << PE6) | (1 << PE7) 

#define LCD_READ_DATA_DONE               ( (1 << PE6) | (1 << PE5 ) )
#define LCD_READ_CONTROL_DONE            (1 << PE6)

#define LCD_CONTROL_MASK                 ( ~ ( ( 1 << PE7 ) | ( 1 << PE6 ) | ( 1 << PE5 ) ) )

enum LCDCommand
  {
    LCD_DISPLAY_CLEAR = 0x01,
    LCD_CURSOR_HOME = 0x02,
    LCD_ENTRY_MODE_NORMAL = 0x06,
    LCD_DISPLAY_ON = 0x0f,
	LCD_DISPLAY_OFF = 0x08,
//    LCD_SHIFT_LEFT = 0x18,
//    LCD_SHIFT_RIGHT = 0x1c,
    LCD_SET_8BITMODE = 0x38,
//    LCD_SET_4BITMODE = 0x28
  };

typedef uint8_t LCDFontChar[ 8 ];
typedef LCDFontChar * LCDFont;

//LCD_Parameter
/** Width of the LCD */
#define LCD_WIDTH  8		

/** Number of rows per character */
#define LCD_FONT_HEIGHT	8	

void initLCDSubSystem( void );
void printBannerLCD( void );
void clearLCD( void );
void controlLCD ( enum LCDCommand command );
/** Define the shiftLCD function as a synonym for controlLCD */
#define shiftLCD( c ) controlLCD( c )

void printStringLCD( uint8_t const row, uint8_t  const col, char const *msg);
void printHexLCD( uint8_t const row, uint8_t  const col, uint16_t value );
void printHexByteLCD( uint8_t const row, uint8_t const col, uint8_t value );
void printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data);
void downloadFontLCD( LCDFont font, int n );
void setPositionLCD(uint8_t  const row, uint8_t const col);
unsigned char convertToHex( uint8_t const v );

/* Private Functions not protected by Semaphore. Use with care */
void _printStringLCD( uint8_t const row, uint8_t  const col, char const *msg);
void _printHexLCD( uint8_t const row, uint8_t  const col, uint16_t value );
void _printHexByteLCD( uint8_t const row, uint8_t const col, uint8_t value );
void _printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data);
void _downloadFontLCD( LCDFont font, int n );


extern volatile Semaphore LCD_lock;

#endif /* _LCD_DRIVER_H_ */
