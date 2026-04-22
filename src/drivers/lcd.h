#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "system.h"

#define LCD_E			LATDbits.LATD4	
#define LCD_TRIS_E		TRISDbits.TRISD4
#define LCD_RW			LATDbits.LATD5
#define LCD_TRIS_RW		TRISDbits.TRISD5
#define LCD_RS			LATBbits.LATB15
#define LCD_TRIS_RS		TRISBbits.TRISB15

#define LCD_DATA        LATE
#define LCD_TRISDATA	TRISE

#define LCD_CLK	{LCD_E = 1; Nop(); Nop(); Nop(); LCD_E = 0;}
						
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_write_char(unsigned char);
void lcd_home();
void lcd_clear();
void lcd_write_line(unsigned int row, const char *str);

#endif