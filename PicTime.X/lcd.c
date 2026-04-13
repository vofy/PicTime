#include <xc.h>
#define FCY 8000000			// must be set in Hz
#include <libpic30.h>
#include "lcd.h"

void initLcd()
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
	cmdLcd(0x38);		// function set: 8bit,2lines display,5x8dots/char
	cmdLcd(0x0C);		// display On/Off: display On, cursor Off,Blink Off
	cmdLcd(0x06);		// entry mode set:DDRAM++
	cmdLcd(0x01);		// clear display
}

void cmdLcd(unsigned char cmd)
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

void dataLcd(unsigned char data)
{
	LCD_RW = 0;
	LCD_RS = 1;
	LCD_DATA &= 0xFF00;
	LCD_DATA |= data;
	LCD_CLK;
	LCD_RS = 0;
	__delay_us(40);
}


void writeLineLcd(char* data)
{
  	unsigned char i = 0;

	for(i=0; i<16; i++)
	{
	  	if(*data!=0x00)
	    		dataLcd(*data++);
	  	else
	    		dataLcd(' ');
	}
}

// return home ddram = 0
void homeLcd()
{
	cmdLcd(0x02);			// return home
}

// clear display
void clearLcd()
{
	cmdLcd(0x01);			// return home
}

// address of 1st line 0 - 15
void setAddr1Lcd(unsigned char col)
{
	if(col>15)
		return;
	cmdLcd(col|0x80);
}

// address of 2nd line 0 - 15
void setAddr2Lcd(unsigned char col)
{
	if(col>15)
		return;
	col += 0x40;	
	cmdLcd(col|0x80);
}

// lenght string , nmr 1-16
void writeStringLcd(char* data, unsigned char nmr)
{
	if(nmr>16)
		return;
	unsigned char i;	
	for(i=0; i<nmr; i++)
		dataLcd(*data++);
}


