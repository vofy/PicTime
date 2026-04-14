#include <xc.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "rtcc.h"
#include "lcd.h"
#include "state.h"

char lineBuffer[17] = "\0";


void draw_CLOCK(void)
{
    IFS0bits.T1IF = 0;
    struct tm current_time;
    rtcc_get_time(&current_time);

    sprintf(lineBuffer, " %02d:%02d:%02d   WK%01d",
        current_time.tm_hour,
        current_time.tm_min,
        current_time.tm_sec,
        rtcc_week_number(&current_time)
    );
    lcd_write_at(0, 0, lineBuffer, true);

    sprintf(lineBuffer, "%02d.%02d.%04d   %s",
        current_time.tm_mday,
        current_time.tm_mon + 1,
        current_time.tm_year + 1900,
        rtcc_weekday_str(&current_time)
    );
    lcd_write_at(1, 0, lineBuffer, true);
}

void draw_STOPWATCH(void)
{        
    time_t diff = rtcc_stopwatch_time();
    char state[7] = "\0";
    
    switch(state_get_current())
    {
        case STATE_STOPWATCH_RUN:
            strcpy(state, " [RUN]");
            break;
        case STATE_STOPWATCH_LAP:
            strcpy(state, " [LAP]");
            break;
        case STATE_STOPWATCH_STOP:
            strcpy(state, "[STOP]");
            break;
        default:
            break;
    }
    
    sprintf(lineBuffer, "STOPWATCH %s", state);
    lcd_write_at(0, 0, lineBuffer, true);
    
    sprintf(lineBuffer, "%02d:%02d:%02d", 
        (int)(diff / 3600), 
        (int)((diff % 3600) / 60), 
        (int)(diff % 60)
    );
    lcd_write_at(1, 0, lineBuffer, true);
}

void draw_ALARM(void)
{
    //sprintf(lineBuffer, "MOD ALARM");
    lcd_write_at(0, 0, "MOD ALARM", true);
    lcd_write_at(1, NULL, NULL, true);
}

void draw_OPTIONS(void)
{
    //sprintf(lineBuffer, "MOD OPTIONS");
    lcd_write_at(0, 0, "MOD OPTIONS", true);
    lcd_write_at(1, NULL, NULL, true);
}