#include <xc.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "views.h"
#include "../drivers/rtcc.h"
#include "../drivers/lcd.h"
#include "../core/stopwatch.h"
#include "../core/alarm.h"
#include "../core/options.h"


void draw_screen_clock(void)
{
    IFS0bits.T1IF = 0;
    struct tm current_time;
    rtcc_get_time(&current_time);
    
    char lineBuffer[17] = "\0";

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
    char lineBuffer[17] = "\0";
    
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
    uint32_t centis  = (time % 1000UL) / 10UL;

    sprintf(lineBuffer, "%02lu:%02lu:%02lu.%02lu",
        hours, minutes, seconds, centis);
    
    lcd_write_line(1, lineBuffer);
}

void draw_screen_alarm(void)
{
    struct tm time = alarm_get_time();
    
    char alarm_en[11];
    char hr[6];
    char min[6];
    char day_en[16];
    char lineBuffer[17] = "\0";

    AlarmState state = alarm_state_get_current();
    const char* state_str = alarm_is_day_enabled(time.tm_wday) ? "ON" : "OFF";

    sprintf(alarm_en, (state == ALARM_ENABLED) ? "<%s>" : "%s", alarm_is_enabled() ? "ENABLED" : "DISABLED");
    sprintf(hr,       (state == ALARM_HOUR) ? "<%02d>" : "%02d", time.tm_hour);
    sprintf(min,      (state == ALARM_MIN) ? "<%02d>" : "%02d", time.tm_min);
    sprintf(day_en,   (state == ALARM_DAYS) ? "<%s-%s>" : "%s-%s", weekday_strings[time.tm_wday], state_str);

    sprintf(lineBuffer, "ALARM %-10s", alarm_en);
    lcd_write_line(0, lineBuffer);

    sprintf(lineBuffer, "%s:%s %-11s", hr, min, day_en);
    lcd_write_line(1, lineBuffer);
}

void draw_screen_options(void)
{
    struct tm time;
    rtcc_get_time(&time); 
    
    OptionsState state = options_state_get_current();
    
    char yr[7];
    char mon[5];
    char day[5];
    char hr[5];
    char min[5];
    char sec[5];
    
    char temp_buf[17];
    char lineBuffer[17] = "\0";

    sprintf(yr,  (state == OPTIONS_YEAR)  ? "<%04d>" : "%04d", time.tm_year + 1900);
    sprintf(mon, (state == OPTIONS_MONTH) ? "<%02d>" : "%02d", time.tm_mon + 1);
    sprintf(day, (state == OPTIONS_DAY)   ? "<%02d>" : "%02d", time.tm_mday);

    sprintf(hr,  (state == OPTIONS_HOUR) ? "<%02d>" : "%02d", time.tm_hour);
    sprintf(min, (state == OPTIONS_MIN)  ? "<%02d>" : "%02d", time.tm_min);
    sprintf(sec, (state == OPTIONS_SEC)  ? "<%02d>" : "%02d", time.tm_sec);

    sprintf(temp_buf, "%s-%s-%s", yr, mon, day);
    sprintf(lineBuffer, "D %-14s", temp_buf);
    lcd_write_line(0, lineBuffer);

    sprintf(temp_buf, "%s:%s:%s", hr, min, sec);
    sprintf(lineBuffer, "T %-14s", temp_buf);
    lcd_write_line(1, lineBuffer);
}
