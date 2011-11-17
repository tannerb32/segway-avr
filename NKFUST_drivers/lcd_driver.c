/**
 * Driver for the LCD of the NKFUST Robot
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca>
 *
 */ 

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_driver.h"

volatile Semaphore LCD_lock;

void
initLCDSubSystem( void )
{
  uint8_t i;

  LCD_DATA_PORT_DIR = 0xff;
  LCD_DATA_PORT = 0x00;

  LCD_CONTROL_PORT_DIR = LCD_CONTROL_PORT_DIR | ( (1 << PE7 ) | ( 1 << PE6 ) | ( 1 << PE5 ) );
  LCD_CONTROL_PORT = LCD_CONTROL_PORT & ( ~ ( (1 << PE7 ) | ( 1 << PE6 ) | ( 1 << PE5 ) ) );

  for( i = 0; i < 2; i++ )
    {
      _delay_ms( 10 );	         	
      controlLCD( LCD_SET_8BITMODE );	
      controlLCD( LCD_DISPLAY_ON );		
      clearLCD( );
      controlLCD( LCD_ENTRY_MODE_NORMAL );	
      _delay_ms( 10 );	
    }	 
	
	printBannerLCD();
	
	initSemaphore( & LCD_lock, 1 );       
}

void
printBannerLCD( void )
{
  uint8_t i;

  clearLCD();	
  _printStringLCD( 0, 4, "Taibotics" );
  _printStringLCD( 1, 6, "Robot" );
  setPositionLCD( 1, 15 );
  for(i=0;i<50;i++)
    {
  		_delay_ms(10);
	}
  clearLCD();
}

void
clearLCD( void )
{
  controlLCD( LCD_DISPLAY_CLEAR );
  controlLCD( LCD_CURSOR_HOME );
}

void
controlLCD ( enum LCDCommand command )
{
//  _delay_us(10);

  /* LCD_RW=0/Read, LCD_RS=0/Control, LCD_ENABLE=1 */
  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_CONTROL_SETUP_ENABLE;

  LCD_DATA_PORT = command;

  _delay_us(5);

  /* LCD_RW=0, LCD_RS=0, LCD_ENABLE=1 */
  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_CONTROL_SETUP;

  _delay_us(5);

  /* LCD_RW=0, LCD_RS=0, LCD_ENABLE=0 */
//  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_CONTROL_DONE;

  _delay_ms(2);
}

void
writeDataLCD( unsigned char const data )
{
  /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=1 */
  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_DATA_SETUP_ENABLE;

  LCD_DATA_PORT = data;

  _delay_us(5);

  /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_DATA_SETUP;

  _delay_us(2);

  /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
//  PORTE = ( PORTE & ( LCD_CONTROL_MASK) ) | LCD_WRITE_DATA_DONE;
}

void
setPositionLCD(unsigned char const row, unsigned char const col)
{
  char addr;
  addr = 0x80 + 0x40 * row + col;
  controlLCD( addr );
}

void
printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data)
{
	downSemaphore( & LCD_lock );
	_printCharAtPositionLCD( row, col, data );
	upSemaphore( & LCD_lock );
}

void
_printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data)
{
  setPositionLCD( row, col );
  writeDataLCD( data );
} 

void
printStringLCD( unsigned char const row, unsigned char const col, char const *msg)
{
	downSemaphore( & LCD_lock );
	_printStringLCD( row, col, msg );
	upSemaphore( & LCD_lock );
}

void
_printStringLCD( unsigned char const row, unsigned char const col, char const *msg)
{
  setPositionLCD( row, col );
  while ( *msg )
    {
      writeDataLCD( *( msg++ ) );
	  _delay_ms(1);
    }
}

void
printHexLCD( uint8_t const row, uint8_t const col, uint16_t value )
{
	downSemaphore( & LCD_lock );
	_printHexLCD( row, col, value );
	upSemaphore( & LCD_lock );
}

void
_printHexLCD( uint8_t const row, uint8_t const col, uint16_t value )
{
  unsigned char buffer[4];
  uint8_t i;
  uint8_t v;
  setPositionLCD( row, col );

  for(i = 0; i < 4; i++ )
    {
      v = value & 0x0f;
      buffer[ 3 - i ] = convertToHex( v );
      value = value >> 4;
    }
  for(i = 0; i < 4; i++ )
    {
      writeDataLCD( buffer[ i ] );
	  _delay_ms(1);
    }
}

void
printHexByteLCD( uint8_t const row, uint8_t const col, uint8_t value )
{
  unsigned char buffer[2];
  uint8_t i;
  uint8_t v;
  setPositionLCD( row, col );
  for(i = 0; i < 2; i++ )
    {
      v = value & 0x0f;
      buffer[ 1 - i ] = convertToHex( v );
      value = value >> 4;
    }
  for(i = 0; i < 2; i++ )
    {
      writeDataLCD( buffer[ i ] );
    }
}

unsigned char font[8][8] =
  {
    //Heart0
    { 0x00, 0x00, 0x0a, 0x1f, 0x1f, 0x0e, 0x04, 0x00 },
    //Note 1
    { 0x00, 0x0c, 0x0f, 0x0b, 0x09, 0x19, 0x1b, 0x03 },
    //B_Full   2
    { 0x00, 0x0e, 0x1f, 0x17, 0x1f, 0x1f, 0x1f, 0x1f },
    //B_Medium 3
    { 0x00, 0x0e, 0x1f, 0x11, 0x13, 0x17, 0x1f, 0x1f },
    //B_Low    4
    { 0x00, 0x0e, 0x1f, 0x11, 0x11, 0x11, 0x13, 0x1f },
    //Y    5
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    //Blank6
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    //Blank7
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
  };


void
downloadFontLCD( LCDFont font, int n )
{
	downSemaphore( & LCD_lock );
	downloadFontLCD( font, n );
	upSemaphore( & LCD_lock );
}

void
_downloadFontLCD( LCDFont font, int n )
{
  int i, j;
  for (i = 0; i < n; i++)
    {
      for ( j = 0; j < LCD_FONT_HEIGHT; j++ )
	{
	  controlLCD( 0x40 + i * 8 + j );
	  writeDataLCD( font[i][j] );
	}
    }
}

unsigned char
convertToHex( uint8_t const v )
{
  static unsigned char const bin2Ascii[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

  unsigned char c = '?';

  if ( v < 16 ) 
    {
      c = bin2Ascii[ v ];
    }
  return c;
}
