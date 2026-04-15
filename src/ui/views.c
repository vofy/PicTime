#include <xc.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "views.h"
#include "../drivers/rtcc.h"
#include "../drivers/lcd.h"
#include "../core/stopwatch.h"

char lineBuffer[17] = "\0";


void draw_screen_clock(void)
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
    lcd_write_line(0, lineBuffer);

    sprintf(lineBuffer, "%02d.%02d.%04d   %s",
        current_time.tm_mday,
        current_time.tm_mon + 1,
        current_time.tm_year + 1900,
        rtcc_weekday_str(&current_time)
    );
    lcd_write_line(1, lineBuffer);
}

void draw_screen_stopwatch(void)
{
    uint32_t time = stopwatch_get_time();
    char state[7] = "\0";
    
    switch(stopwatch_state_get_current())
    {
        case SW_RUN:
            strcpy(state, " [RUN]");
            break;
        case SW_LAP:
            strcpy(state, " [LAP]");
            break;
        case SW_STOP:
            strcpy(state, "[STOP]");
            break;
        default:
            break;
    }
    sprintf(lineBuffer, "Stopwatch %s", state);
    lcd_write_line(0, lineBuffer);

    uint32_t hours   =  time / 3600000UL;
    uint32_t minutes = (time % 3600000UL) / 60000UL;
    uint32_t seconds = (time % 60000UL) / 1000UL;
    uint32_t centis  = (time % 1000UL) / 10UL;   // hundredths of a second

    sprintf(lineBuffer, "%02lu:%02lu:%02lu.%02lu",
        hours, minutes, seconds, centis);
    
    lcd_write_line(1, lineBuffer);
}

void draw_screen_alarm(void)
{
    lcd_write_line(0, "ALARM");
    lcd_write_line(1, "");
}

void draw_screen_options(void)
{
    lcd_write_line(0, "OPTIONS");
    lcd_write_line(1, "");
}