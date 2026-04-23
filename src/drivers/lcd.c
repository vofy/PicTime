#include <xc.h>
#include "lcd.h"

void lcd_init()
{
	// LCD ports
	LCD_DATA &= 0xFF00;
	LCD_E = 0;
	LCD_RW = 0;
	LCD_RS = 0;	
	LCD_TRISDATA &= 0xFF00;
	LCD_TRIS_E = 0;
	LCD_TRIS_RW = 0;
	LCD_TRIS_RS = 0;
	__delay_ms(15);		
	
	LCD_DATA &= 0xFF00;
	LCD_DATA |= 0x0038;
	LCD_CLK;
 	__delay_ms(5);
	
	LCD_DATA &= 0xFF00;
	LCD_DATA |= 0x0038;
	LCD_CLK;
  	__delay_us(150);

	lcd_cmd(0x38);		// 8 bit, 2 lines display, 5x8dots/char
	lcd_cmd(0x0C);		// Display On, cursor Off, Blink Off
	lcd_cmd(0x06);		// Entry mode set: DDRAM++
	lcd_cmd(0x01);		// Clear display
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
	lcd_cmd(0x02);
}

void lcd_clear()
{
	lcd_cmd(0x01);
}

void lcd_write_line(unsigned int row, const char *str)
{
    unsigned int addr = (row == 1 ? 0x40 : 0x00);
    lcd_cmd(0x80 | addr);

    for (unsigned int i = 0; i < 16; i++)
        lcd_write_char(*str ? *str++ : ' ');
}