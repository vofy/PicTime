#include <xc.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "rtcc.h"
#include "adc.h"

#define MODE_BTN			PORTDbits.RD6
#define NEXT_BTN			PORTDbits.RD7
#define ENTER_BTN			PORTAbits.RA7
#define ESC_BTN             PORTDbits.RD13

#define countof(a) (int)(sizeof(a) / sizeof(*(a)))

#define mode_enum_count 4

typedef enum Mode {TIME, ALARM, STOPWATCH, OPTIONS} Mode;

typedef enum Option {OPT_TIME} Option;
typedef enum Time_Option {HOUR, MIN, SEC} Time_Option;


_CONFIG1 (0x3F7F)	// Watchdog off, JTAG off, Code protection off
_CONFIG2 (0xF99F)	// primary osc off, FRC without PLL

void led_init()
{
    TRISAbits.TRISA0 = 0;
}

void timer_init()
{
    T1CON = 0x0020;			// fosc/2 =>0.25us*64=16us
 	PR1 = 31250;          	// 16us*31250 = 500ms
 	T1CONbits.TON = 1;		// Timer1 on
 	IFS0bits.T1IF = 0;		// interrupt flag
 	IEC0bits.T1IE = 0;		// interrup 
}

void init(void)
{
    lcd_init();
    rtcc_init();
    timer_init();
    //adc_init();
    led_init();
}

int main(void)
{
	init();
    
    char lineBuffer[17] = "\0";
    Mode mode = TIME;
    
    Option opt = TIME;
    Time_Option time_opt = HOUR;
    
    struct tm time = {
        .tm_year = 2026,
        .tm_mon  = 3,   // Months are indexed from 0 (ISO 8601)
        .tm_mday = 19,
        .tm_hour = 23,
        .tm_min  = 59,
        .tm_sec  = 55,
        .tm_wday = 3
    };

    rtcc_set_time(&time);

	while(1)
  	{
        if(!MODE_BTN)
        {
            while(!MODE_BTN);
            mode = ++mode % mode_enum_count;
        }
        
        switch (mode){
            case TIME:
                if(IFS0bits.T1IF)
                {
                    IFS0bits.T1IF = 0;
                    LATAbits.LATA0 ^= 1; // Alarm blink led
                    
                    rtcc_get_time(&time);

                    sprintf(lineBuffer, " %02d:%02d:%02d   WK%01d",
                        time.tm_hour,
                        time.tm_min,
                        time.tm_sec,
                        rtcc_week_number(&time)
                    );
                    lcd_write_at(0, 0, lineBuffer, true);    

                    sprintf(lineBuffer, "%02d.%02d.%04d   %s",
                        time.tm_mday,
                        time.tm_mon + 1,
                        time.tm_year + 1900,
                        rtcc_weekday_str(&time)
                    );
                    lcd_write_at(1, 0, lineBuffer, true); 
                }
                break;
            case ALARM:
                sprintf(lineBuffer, "ALARM M");
                lcd_write_at(0, 0, lineBuffer, true);
                lcd_write_at(1, NULL, NULL, true);
                break;
            case STOPWATCH:
                sprintf(lineBuffer, "STOPWATCH M");
                lcd_write_at(0, 0, lineBuffer, true);
                lcd_write_at(1, NULL, NULL, true);
                break;
            case OPTIONS:
                rtcc_get_time(&time);
                
                if(!NEXT_BTN)
                {
                    while(!NEXT_BTN);
                    mode = ++mode % mode_enum_count;
                }

                switch(opt)
                {
                    case TIME:
                    {
                        char hour[5] = "\0";
                        char min[5] = "\0";
                        char sec[5] = "\0";

                        sprintf(hour, time_opt == HOUR ? "<%02d>" : "%02d", time.tm_hour);
                        sprintf(min,  time_opt == MIN  ? "<%02d>" : "%02d", time.tm_min);
                        sprintf(sec,  time_opt == SEC  ? "<%02d>" : "%02d", time.tm_sec);  

                        sprintf(lineBuffer, "TIME %s:%s:%s", hour, min, sec);

                        break;
                    }
                }
                
                lcd_write_at(0, 0, lineBuffer, true);
                lcd_write_at(1, NULL, NULL, true);
                
                break;
        }
 	}
    
    return 0;
}