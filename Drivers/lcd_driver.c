/**
 * Driver for the LCD of the NKFUST Robot
 *
 * Jacky Baltes <jacky@cs.umanitoba.ca>
 *
 */

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#if defined(USE_LCD)
#   include "lcd_driver.h"
#endif /* USE_LCD */

void initLCDSubSystem(void)
{
    LCD_DATA_PORT_DIR = LCD_DATA_PORT_DIR | LCD_DATA_PORT_MASK;
    LCD_DATA_PORT = LCD_DATA_PORT & (~ LCD_DATA_PORT_MASK);
    LCD_CONTROL_PORT_DIR = LCD_CONTROL_PORT_DIR | (LCD_CONTROL_PORT_MASK);
    LCD_CONTROL_PORT = LCD_CONTROL_PORT & (~(LCD_CONTROL_PORT_MASK));
    _delay_ms(20);
    _writeLCD_DATA_PORT(LCD_INIT_HAIL);
    _writeControlLCD(LCD_COMMAND_IGNORE);
    _delay_ms(6);
    _writeLCD_DATA_PORT(LCD_INIT_HAIL);
    _writeControlLCD(LCD_COMMAND_IGNORE);
    _delay_ms(1);
    _writeLCD_DATA_PORT(LCD_INIT_HAIL);
    _writeControlLCD(LCD_COMMAND_IGNORE);
    _delay_ms(1);
    _writeLCD_DATA_PORT(LCD_SET_INTERFACE_4BIT);
    _writeControlLCD(LCD_COMMAND_IGNORE);
    _delay_ms(1);
#if LCD_MODE == 8
    _writeControlLCD(LCD_SET_8BITMODE);
#elif LCD_MODE == 4
    _writeControlLCD(LCD_SET_4BITMODE);
#else
#   error "Unknown LCD Mode"
#endif /* LCD_MODE */
    _delay_ms(1);
    /*
        _writeControlLCD( LCD_DISPLAY_OFF );
        _delay_ms(1);

        _writeControlLCD( LCD_DISPLAY_CLEAR );
        _delay_ms(1);
    */
    _writeControlLCD(LCD_DISPLAY_ON);
    _delay_ms(1);
    _writeControlLCD(LCD_ENTRY_MODE_INC);
    _delay_ms(1);
    printBannerLCD();
}

void _writeLCD_DATA_PORT(uint8_t data)
{
    LCD_DATA_PORT = (LCD_DATA_PORT & (~ LCD_DATA_PORT_MASK)) | (data << LCD_DATA_PORT_SHIFT);
}

void printBannerLCD(void)
{
    uint8_t i;
    clearLCD();
    printStringLCD(0, 4, "Taibotics");
    printStringLCD(1, 6, "Robot");
    setPositionLCD(1, 15);

    for (i = 0; i < 100; i++)
    {
        _delay_ms(10);
    }

    clearLCD();
}

void clearLCD(void)
{
    _writeControlLCD(LCD_DISPLAY_CLEAR);
    _delay_ms(5);
    _writeControlLCD(LCD_CURSOR_HOME);
    _delay_ms(5);
}

void _writeControlLCD(enum LCDCommand const command)
{
#if LCD_MODE == 4
    uint8_t i;
    uint8_t data;
    uint8_t stop;
#endif
#if LCD_MODE == 8
    /* LCD_RW=0/Read, LCD_RS=0/Control, LCD_ENABLE=1 */
    LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~ LCD_CONTROL_PORT_MASK)) | LCD_WRITE_CONTROL_SETUP_ENABLE;

    if (command != LCD_COMMAND_IGNORE)
    {
        _writeLCD_DATA_PORT(command);
    }

    _delay_us(10);
    /* LCD_RW=0, LCD_RS=0, LCD_ENABLE=0 */
    LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_CONTROL_SETUP;
    LCD_COMMAND_DELAY();
    /* LCD_RW=0, LCD_RS=0, LCD_ENABLE=0 */
    //  LCD_CONTROL_PORT = ( LCD_CONTROL_PORT & ( LCD_CONTROL_PORT_MASK) ) | LCD_WRITE_CONTROL_DONE;
    //  _delay_ms(3);
#elif LCD_MODE == 4
    data = command;

    if (command == LCD_COMMAND_IGNORE)
    {
        stop = 1;
    }
    else
    {
        stop = 2;
    }

    for (i = 0; i < stop; i++)
    {
        /* LCD_RW=0/Read, LCD_RS=0/Control, LCD_ENABLE=1 */
        LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~ LCD_CONTROL_PORT_MASK)) | LCD_WRITE_CONTROL_SETUP_ENABLE;

        if (command != LCD_COMMAND_IGNORE)
        {
            _writeLCD_DATA_PORT((data >> 4) & 0x0f);
        }

        _delay_us(10);
        /* LCD_RW=0, LCD_RS=0, LCD_ENABLE=0 */
        LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_CONTROL_SETUP;
        LCD_COMMAND_DELAY();
        data = data << 4;
    }

#else
#   error   "Unknown LCD_MODE"
#endif
}

void _writeDataLCD(unsigned char data)
{
#if LCD_MODE == 4
    uint8_t i;
#endif
#if LCD_MODE == 8
    /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=1 */
    LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_DATA_SETUP_ENABLE;
    _writeLCD_DATA_PORT(data);
    _delay_us(10);
    /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
    LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_DATA_SETUP;
    LCD_COMAMND_DELAY();
    /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
    //  LCD_CONTROL_PORT = ( LCD_CONTROL_PORT & ( LCD_CONTROL__PORT_MASK) ) | LCD_WRITE_DATA_DONE;
#elif LCD_MODE == 4

    for (i = 0; i < 2; i++)
    {
        /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=1 */
        LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_DATA_SETUP_ENABLE;
        _writeLCD_DATA_PORT((data >> 4) & 0x0f);
        _delay_us(10);
        /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
        LCD_CONTROL_PORT = (LCD_CONTROL_PORT & (~LCD_CONTROL_PORT_MASK)) | LCD_WRITE_DATA_SETUP;
        LCD_COMMAND_DELAY();
        /* LCD_RW=0/Read, LCD_RS=1/Data, LCD_ENABLE=0 */
        //  LCD_CONTROL_PORT = ( LCD_CONTROL_PORT & ( LCD_CONTROL__PORT_MASK) ) | LCD_WRITE_DATA_DONE;
        data = (data << 4);
    }

#else
#   error "Unknown LCD_MODE"
#endif
    _delay_ms(3);
}

void setPositionLCD(unsigned char const row, unsigned char const col)
{
    char addr;
    addr = 0x80 + 0x40 * row + col;
    _writeControlLCD(addr);
}

void printCharAtPositionLCD(unsigned char const row, unsigned char const col, unsigned char const data)
{
    setPositionLCD(row, col);
    _writeDataLCD(data);
}

void printIntegerLCD(uint8_t const row, uint8_t  const col, uint16_t value, uint8_t radix)
{
    setPositionLCD(row, col);
    char msg[17];
    char *c = &msg;
    itoa(value, &msg, radix);

    while (*c)
    {
        _writeDataLCD(*c);
        _delay_ms(1);
        c++;
    }
}

void printStringLCD(unsigned char const row, unsigned char const col, char const *msg)
{
    setPositionLCD(row, col);

    while (*msg)
    {
        _writeDataLCD(*(msg++));
        _delay_ms(1);
    }
}

void printHexLCD(uint8_t const row, uint8_t const col, uint16_t value)
{
    unsigned char buffer[4];
    uint8_t i;
    uint8_t v;
    setPositionLCD(row, col);

    for (i = 0; i < 4; i++)
    {
        v = value & 0x0f;
        buffer[ 3 - i ] = convertToHex(v);
        value = value >> 4;
    }

    for (i = 0; i < 4; i++)
    {
        _writeDataLCD(buffer[ i ]);
        _delay_ms(1);
    }
}

void printHexByteLCD(uint8_t const row, uint8_t const col, uint8_t value)
{
    unsigned char buffer[2];
    uint8_t i;
    uint8_t v;
    setPositionLCD(row, col);

    for (i = 0; i < 2; i++)
    {
        v = value & 0x0f;
        buffer[ 1 - i ] = convertToHex(v);
        value = value >> 4;
    }

    for (i = 0; i < 2; i++)
    {
        _writeDataLCD(buffer[ i ]);
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


void downloadFontLCD(LCDFont font, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < LCD_FONT_HEIGHT; j++)
        {
            _writeControlLCD(0x40 + i * 8 + j);
            _writeDataLCD(font[i][j]);
        }
    }
}

unsigned char convertToHex(uint8_t const v)
{
    static unsigned char const bin2Ascii[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    unsigned char c = '?';

    if (v < 16)
    {
        c = bin2Ascii[ v ];
    }

    return c;
}
