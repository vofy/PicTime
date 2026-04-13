#include <xc.h>
#include <time.h>
#include <stdio.h>
#include "lcd.h"
#include "rtcc.h"

#define MODE_BTN			PORTDbits.RD6
#define UP_BTN				PORTDbits.RD7
#define DOWN_BTN			PORTAbits.RA7
#define SET_SNOOZE_BTN      PORTDbits.RD13

#define countof(a) (int)(sizeof(a) / sizeof(*(a)))

typedef enum {TIME, ALARM, STOPWATCH, SETTINGS} Mode;
#define mode_enum_count 4


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
}

void main(void)
{
	init();
    
    char lineBuffer[20] = "\0";
    Mode mode = SETTINGS;
    const struct tm time = {
        .tm_year = 2026,
        .tm_mon  = 4 - 1,
        .tm_mday = 19,
        .tm_hour = 23,
        .tm_min  = 59,
        .tm_sec  = 55,
        .tm_wday = 3
    };

    rtcc_set_tm(&time);

	while(1)
  	{        
        if(!MODE_BTN)
        {
            while(!MODE_BTN);
            mode = ++mode % mode_enum_count;
        }
        
        //LATAbits.LATA0 ^= 1; -- Alarm blink led
        
        switch (mode){
            case TIME:
                if(IFS0bits.T1IF)
                {
                    IFS0bits.T1IF = 0;

                    rtcc_get_tm(&time);

                    homeLcd();

                    sprintf(lineBuffer, " %02d:%02d:%02d   WK%01d",
                        time.tm_hour,
                        time.tm_min,
                        time.tm_sec,
                        rtcc_week_number(&time)
                    );
                    writeLineLcd(lineBuffer);    

                    sprintf(lineBuffer, "%02d.%02d.%04d   %s",
                        time.tm_mday,
                        time.tm_mon + 1,
                        time.tm_year + 1900,
                        rtcc_weekday_str(&time)
                    );
                    writeLineLcd(lineBuffer);
                }
                break;
            case ALARM:
                homeLcd();
                sprintf(lineBuffer, "ALARM M");
                writeLineLcd(lineBuffer);
                break;
            case STOPWATCH:
                homeLcd();
                sprintf(lineBuffer, "STOPWATCH M");
                writeLineLcd(lineBuffer);
                break;
            case SETTINGS:
                homeLcd();
                sprintf(lineBuffer, "SETTINGS M");
                writeLineLcd(lineBuffer);
                break;
        }
 	}			
}