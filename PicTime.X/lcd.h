#ifndef LCD_H
#define	LCD_H

// pins;
#define LCD_E			LATDbits.LATD4	
#define LCD_TRIS_E		TRISDbits.TRISD4
#define LCD_RW			LATDbits.LATD5
#define LCD_TRIS_RW		TRISDbits.TRISD5
#define LCD_RS			LATBbits.LATB15
#define LCD_TRIS_RS		TRISBbits.TRISB15

#define LCD_DATA        LATE
#define LCD_TRISDATA	TRISE

// macros
#define LCD_CLK	{LCD_E = 1; Nop(); Nop(); Nop(); LCD_E = 0;}

// functions							
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_write_char(unsigned char);
void lcd_home();
void lcd_clear();
void lcd_write_at(unsigned int row, unsigned int col, const char *str, bool blank_fill);

#endif	/* LCD_H */

