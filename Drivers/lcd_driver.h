/**
 * Driver for the LCD of the NKFUST Robot
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca> 
 *
 */ 

#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include <inttypes.h>

#if ROBOT == 1
/* LCD_MODE == 0 :- Eight bit mode */
#define LCD_MODE   8

#define LCD_DATA_PORT			PORTA
#define LCD_DATA_PORT_DIR       DDRA

#define LCD_CONTROL_PORT		PORTE 		
#define LCD_CONTROL_PORT_DIR	DDRE 		

/* Not sure if these are working anymore, since I do not have the hardware right now. JB */

#define LCD_BIT_REGISTER_SELECT         5  
#define LCD_BIT_READ_WRITE				6
#define LCD_BIT_OP_START				7

#elif ROBOT == 2

/* LCD_MODE == 1 :- Four bit mode */
#define LCD_MODE   4

#define LCD_DATA_PORT          (PORTA)
#define LCD_DATA_PORT_DIR      DDRA

#define LCD_DATA_PORT_MASK     ( (1 << PA7) | (1 << PA6) | ( 1 << PA5) | (1 << PA4) )
#define LCD_DATA_PORT_SHIFT    4

#define LCD_CONTROL_PORT       PORTA 		
#define LCD_CONTROL_PORT_DIR   DDRA

#define LCD_BIT_REGISTER_SELECT    0
#define LCD_BIT_READ_WRITE         1
#define LCD_BIT_OP_START           2
#elif ROBOT == 3

/* LCD_MODE == 1 :- Four bit mode */
#define LCD_MODE   4

#define LCD_DATA_PORT          (PORTA)
#define LCD_DATA_PORT_DIR      DDRA

#define LCD_DATA_PORT_MASK     ( (1 << PA7) | (1 << PA6) | ( 1 << PA5) | (1 << PA4) )
#define LCD_DATA_PORT_SHIFT    4

#define LCD_CONTROL_PORT       PORTA 		
#define LCD_CONTROL_PORT_DIR   DDRA

#define LCD_BIT_REGISTER_SELECT    0
#define LCD_BIT_READ_WRITE         1
#define LCD_BIT_OP_START           2
#else
#   error "Missing robot definition"
#endif

#if ! defined(LCD_BIT_REGISTER_SELECT)
#   error "Missing definition of LCD_BIT_REGISTER_SELECT"
#endif

#if ! defined(LCD_BIT_READ_WRITE)
#   error "Missing definition of LCD_BIT_READ_WRITE"
#endif
  
#if ! defined(LCD_BIT_OP_START)
#   error "Missing definition of LCD_BIT_OP_START"
#endif


#if LCD_MODE == 8
#   define LCD_INIT_HAIL				(0x30)
#   define LCD_DATA_PORT_MASK			( (1 << PA7) | (1 << PA6) | ( 1 << PA5) | (1 << PA4) | ( 1 << PA3) | (1 << PA2) | (1 << PA1) | (1 << PA0) )
#   define LCD_DATA_PORT_SHIFT			0
#elif LCD_MODE == 4
#   define LCD_INIT_HAIL          (0x03)

#   if ! defined(LCD_DATA_PORT_MASK) 
#      error "You must define LCD_DATA_PORT_MASK for 4 bit mode"
#    endif

#    if ! defined(LCD_DATA_PORT_SHIFT) 
#       error "You must define LCD_DATA_PORT_SHIFT for 4 bit mode"
#    endif
#else
#   error "Undefined LCD_MODE"
#endif

#define LCD_COMMAND_DELAY()				do { _delay_us(160); } while(0)

#define LCD_WRITE_DATA_SETUP            (1 << LCD_BIT_REGISTER_SELECT)
#define LCD_WRITE_CONTROL_SETUP         0

#define LCD_WRITE_DATA_SETUP_ENABLE      ( (1 << LCD_BIT_REGISTER_SELECT) | (1 << LCD_BIT_OP_START) )
#define LCD_WRITE_CONTROL_SETUP_ENABLE                                      (1 << LCD_BIT_OP_START)

#define LCD_WRITE_DATA_DONE              (1 << LCD_BIT_REGISTER_SELECT )
#define LCD_WRITE_CONTROL_DONE           0

#define LCD_READ_DATA_SETUP              ( (1 << LCD_BIT_REGISTER_SELECT) | ( 1 << LCD_BIT_READ_WRITE) )
#define LCD_READ_CONTROL_SETUP                                               (1 << LCD_BIT_READ_WRITE)

#define LCD_READ_DATA_SETUP_ENABLE       ( (1 << LCD_BIT_REGISTER_SELECT) | (1 << LCD_BIT_READ_WRITE) | (1 << LCD_BIT_OP_START) ) )
#define LCD_READ_CONTROL_SETUP_ENABLE                                       (1 << LCD_BIT_READ_WRITE) | (1 << LCD_BIT_OP_START) 

#define LCD_READ_DATA_DONE               ( (1 << PE6) | (1 << PE5 ) )
#define LCD_READ_CONTROL_DONE            (1 << PE6)

#define LCD_CONTROL_PORT_MASK            ( ( 1 << LCD_BIT_REGISTER_SELECT ) | ( 1 << LCD_BIT_READ_WRITE ) | ( 1 << LCD_BIT_OP_START ) )

enum LCDCommand
  {
    LCD_DISPLAY_CLEAR = 0x01,
    LCD_CURSOR_HOME = 0x02,
	LCD_SET_INTERFACE_4BIT = 0x02,
    LCD_ENTRY_MODE_INC = 0x06,            /* Incr. cursor after write */
	LCD_ENTRY_MODE_INC_SHIFT = 0x07,      /* Incr. cursor and shift display */
	LCD_ENTRY_MODE_DEC = 0x04,            /* Decr. cursor after write */
	LCD_ENTRY_MODE_DEC_SHIFT = 0x05,      /* Decr cursor and shift */
	
	LCD_DISPLAY_OFF = 0x08,

	LCD_DISPLAY_ON = 0x0c,
	LCD_DISPLAY_ON_CURSOR = 0x0e,
    LCD_DISPLAY_ON_CURSOR_BLINK = 0x0f,
	
    LCD_SHIFT_LEFT = 0x18,
    LCD_SHIFT_RIGHT = 0x1c,
	
    LCD_SET_8BITMODE = 0x38,
    LCD_SET_4BITMODE = 0x28,
	
	LCD_DD_RAM_ADDR = 0x80,
	LCD_DD_RAM_UPPER_LEFT = 0x80, /* Upper left corner of the display? */
	
	LCD_COMMAND_IGNORE = 0xff
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
void _writeControlLCD ( enum LCDCommand command );
void _writeLCD_DATA_PORT( uint8_t data);

void printStringLCD( uint8_t const row, uint8_t  const col, char const *msg);
void printHexLCD( uint8_t const row, uint8_t  const col, uint16_t value );
void printHexByteLCD( uint8_t const row, uint8_t const col, uint8_t value );
void printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data);
void downloadFontLCD( LCDFont font, int n );
void setPositionLCD(uint8_t  const row, uint8_t const col);
unsigned char convertToHex( uint8_t const v );

#endif /* _LCD_DRIVER_H_ */
