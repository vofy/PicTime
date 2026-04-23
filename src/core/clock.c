#include <xc.h>
#include <stdlib.h>
#include <stdio.h>

#include "clock.h"
#include "../drivers/rtcc.h"
#include "../drivers/eeprom.h"
#include "../drivers/lcd.h"

static const char* weekday_strings[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void clock_init(void)
{
    struct tm default_time = {
        .tm_year = 126,
        .tm_mon  = 0,
        .tm_mday = 1,
        .tm_hour = 0,
        .tm_min  = 0,
        .tm_sec  = 0
    };
    clock_set_time(&default_time);
}

void clock_set_time(struct tm *t)
{
    mktime(t);
    rtcc_set_time(t);
}

const char *clock_get_weekday_str(struct tm *t)
{
    if (t->tm_wday < 0 || t->tm_wday > 6) return "??";
    return weekday_strings[t->tm_wday];
}

const char *clock_get_weekday_name(int day_index)
{
    if (day_index < 0 || day_index > 6) return "??";
    return weekday_strings[day_index];
}

int clock_get_week_number(struct tm *t)
{
    struct tm tmp = *t;
    time_t ts = mktime(&tmp);
    struct tm *pt = localtime(&ts);

    char buf[3];
    strftime(buf, sizeof(buf), "%V", pt); // ISO week number

    return atoi(buf);
}

void clock_draw_screen(void)
{
    IFS0bits.T1IF = 0;
    
    struct tm current_time;
    rtcc_get_time(&current_time);
    
    char lineBuffer[17];

    sprintf(lineBuffer, " %02d:%02d:%02d   WK%01d",
        current_time.tm_hour,
        current_time.tm_min,
        current_time.tm_sec,
        clock_get_week_number(&current_time)
    );
    lcd_write_line(0, lineBuffer);

    sprintf(lineBuffer, "%02d.%02d.%04d  %s",
        current_time.tm_mday,
        current_time.tm_mon + 1,
        current_time.tm_year + 1900,
        clock_get_weekday_str(&current_time)
    );
    lcd_write_line(1, lineBuffer);
}