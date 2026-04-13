#include <xc.h>
#define FCY 8000000			// must be set in Hz
#include <libpic30.h>
#include <stdbool.h>
#include <string.h>
#include "lcd.h"

void lcd_init()
{
	//ports LCD
	LCD_DATA &= 0xFF00;
	LCD_E = 0;
	LCD_RW = 0;
	LCD_RS = 0;	
	LCD_TRISDATA &= 0xFF00;
	LCD_TRIS_E = 0;
	LCD_TRIS_RW = 0;
	LCD_TRIS_RS = 0;
	__delay_ms(15);		
	
	// 1st
	LCD_DATA &= 0xFF00;
	LCD_DATA |= 0x0038;
	LCD_CLK;
 	__delay_ms(5);
	
	// 2nd
	LCD_DATA &= 0xFF00;
	LCD_DATA |= 0x0038;
	LCD_CLK;
  	__delay_us(150);

	// 3rd
	lcd_cmd(0x38);		// function set: 8bit,2lines display,5x8dots/char
	lcd_cmd(0x0C);		// display On/Off: display On, cursor Off,Blink Off
	lcd_cmd(0x06);		// entry mode set:DDRAM++
	lcd_cmd(0x01);		// clear display
}

void lcd_cmd(unsigned char cmd)
{
	LCD_RW = 0;
	LCD_RS = 0;	
	LCD_DATA &= 0xFF00;
	LCD_DATA |= cmd;
	LCD_CLK;
    
	if(cmd&0xFC)
	{
  		__delay_us(50);	
	}
	else
	{
	 	__delay_ms(2);	
	}
}

void lcd_write_char(unsigned char data)
{
	LCD_RW = 0;
	LCD_RS = 1;
	LCD_DATA &= 0xFF00;
	LCD_DATA |= data;
	LCD_CLK;
	LCD_RS = 0;
	__delay_us(40);
}

void lcd_home()
{
	lcd_cmd(0x02);			// return home
}

void lcd_clear()
{
	lcd_cmd(0x01);			// return home
}

void lcd_write_at(unsigned int row, unsigned int col, const char *str, bool blank_fill)
{
    if (row > 1 || col > 15)
        return;

    unsigned int addr = (row == 1 ? 0x40 : 0x00) + col;
    lcd_cmd(0x80 | addr);

    unsigned int str_len = blank_fill ? 16 : (16 - col);

    for (unsigned int i = 0; i < str_len; i++)
        lcd_write_char(*str ? *str++ : ' ');
}