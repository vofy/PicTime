//*****************************************************************************
// project:		rtcc  
// source:		main.c
// MCU:			PIC24FJ128GA010, Explorer16
//*****************************************************************************
// actual mcu:	p24FJ128GA010.h
// addres:		C:\Program Files (x86)\Microchip\MPLAB C30\support\PIC24F\h

#include <p24fxxxx.h>
#include <stdio.h>
#include "lcd.h"
#include "rtcc.h"

#define MODE_BTN			PORTDbits.RD6
#define UP_BTN				PORTDbits.RD7
#define DOWN_BTN			PORTAbits.RA7
#define SET_BTN             PORTDbits.RD13

#define countof(a) (int)(sizeof(a) / sizeof(*(a)))

typedef enum {TIME, ALARM, STOPWATCH, SETTINGS} Mode;
#define enum_count 4

char charBuffer[20]; 
unsigned char bufferTime[6] = {2,3,1,2,1,0};
unsigned char bufferDate[9] = {1,9,0,2,2,0,1,5,5};

Mode mode;

_CONFIG1 (0x3F7F)	// Watchdog off, JTAG off, Code protection off
_CONFIG2 (0xF99F)	// primary osc off, FRC without PLL

void init(void)
{
    initLcd();
    initRtcc();
	// timer
	T1CON = 0x0020;			// fosc/2 =>0.25us*64=16us
 	PR1 = 31250;          	// 16us*31250 = 500ms
 	T1CONbits.TON = 1;		// Timer1 on
 	IFS0bits.T1IF = 0;		// interrupt flag
 	IEC0bits.T1IE = 0;		// interrupt off
    // sviceni LED
    TRISAbits.TRISA0 = 0;
    // naplneni RTCC
    writeTimeRtcc(bufferTime); // 260 cyklu
    writeDateRtcc(bufferDate); // 260 cyklu
    
    mode = TIME;
}

void main(void)
{
	init();
	while(1)
  	{
        if(!MODE_BTN)
            mode = (mode < enum_count) ? mode + 1 : 0;
        
        switch (mode){
            case TIME:
                if(IFS0bits.T1IF)
                {
                    IFS0bits.T1IF = 0;
                    LATAbits.LATA0 ^= 1;

                    homeLcd();
                    readDateCharRtcc(charBuffer);
                    writeLineLcd(charBuffer);
                    readTimeCharRtcc(charBuffer);
                    writeLineLcd(charBuffer);        
                }
            case ALARM:
                // TODO: Upravit
                break;
            case STOPWATCH:
                break;
            case SETTINGS:
                break;
        }
 	}			
}