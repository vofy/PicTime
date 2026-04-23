#include <xc.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include "options.h"
#include "clock.h"
#include "../drivers/buttons.h"
#include "../drivers/rtcc.h"
#include "../drivers/eeprom.h"
#include "../drivers/lcd.h"

static OptionsState options_state = OPTIONS_DAY;

OptionsState options_state_get_current(void)
{
    return options_state;
}

void options_enter(void)
{
    options_state = OPTIONS_DAY;
}

void options_set_time(struct tm *time)
{
    clock_set_time(time);
}

void options_handle_key(Button button)
{
    if (button == BUTTON_3)
    {
        options_state = (options_state + 1) % OPTIONS_STATES;
        return;
    }

    if (button == BUTTON_2)
    {
        struct tm time;
        rtcc_get_time(&time);

        switch (options_state)
        {
            case OPTIONS_DAY:
                time.tm_mday = (time.tm_mday % 31) + 1;
                break;
                
            case OPTIONS_MONTH:
                time.tm_mon = (time.tm_mon + 1) % 12;
                break;
                
            case OPTIONS_YEAR:
                time.tm_year++;
                if (time.tm_year > 200) time.tm_year = 100;
                break;
                
            case OPTIONS_HOUR:
                time.tm_hour = (time.tm_hour + 1) % 24;
                break;
                
            case OPTIONS_MIN:
                time.tm_min = (time.tm_min + 1) % 60;
                break;
                
            case OPTIONS_SEC:
                time.tm_sec = 0;
                break;
                
            default:
                break;
        }
        
        options_set_time(&time);
    }
}

void options_draw_screen(void)
{
    struct tm time;
    rtcc_get_time(&time);
    
    char year[7];
    char month[5];
    char day[5];
    char hour[5];
    char min[5];
    char sec[5];
    
    char temp_buf[17];
    char lineBuffer[17];

    sprintf(year,  (options_state == OPTIONS_YEAR)  ? "<%04d>" : "%04d", time.tm_year + 1900);
    sprintf(month, (options_state == OPTIONS_MONTH) ? "<%02d>" : "%02d", time.tm_mon + 1);
    sprintf(day,   (options_state == OPTIONS_DAY)   ? "<%02d>" : "%02d", time.tm_mday);

    sprintf(hour,  (options_state == OPTIONS_HOUR) ? "<%02d>" : "%02d", time.tm_hour);
    sprintf(min,   (options_state == OPTIONS_MIN)  ? "<%02d>" : "%02d", time.tm_min);
    sprintf(sec,   (options_state == OPTIONS_SEC)  ? "<%02d>" : "%02d", time.tm_sec);

    sprintf(temp_buf, "%s.%s.%s", day, month, year);
    sprintf(lineBuffer, "D %-14s", temp_buf);
    lcd_write_line(0, lineBuffer);

    sprintf(temp_buf, "%s:%s:%s", hour, min, sec);
    sprintf(lineBuffer, "T %-14s", temp_buf);
    lcd_write_line(1, lineBuffer);
}