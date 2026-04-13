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
void initLcd();
void cmdLcd(unsigned char);
void dataLcd(unsigned char);
void writeLineLcd(char*);
void homeLcd();
void clearLcd();
void setAddr1Lcd(unsigned char);
void setAddr2Lcd(unsigned char);
void writeStringLcd(char*, unsigned char);



#endif	/* LCD_H */

