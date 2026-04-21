#include <xc.h>
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "alarm.h"
#include "../drivers/buttons.h"
#include "../ui/views.h"

static bool alarm_days_enabled[DAYS_IN_WEEK] = {
    [DAY_SUN] = false,
    [DAY_MON] = false, 
    [DAY_TUE] = false, 
    [DAY_WED] = false, 
    [DAY_THU] = false, 
    [DAY_FRI] = false, 
    [DAY_SAT] = false
};

static bool alarm_enabled = false;

const char* const weekday_strings[DAYS_IN_WEEK] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};

static AlarmState current_alarm_state = ALARM_ENABLED;

static struct tm alarm_time = {0};

AlarmState alarm_state_get_current(void)
{
    return current_alarm_state;
}

struct tm alarm_get_time(void)
{
    return alarm_time;
}

bool alarm_is_day_enabled(WeekDay day)
{
    return alarm_days_enabled[day];
}

bool alarm_is_enabled(void)
{
    return alarm_enabled;
}

void alarm_day_toggle(WeekDay day)
{
    alarm_days_enabled[day] = !alarm_days_enabled[day];
}

void alarm_handle_key(Button button)
{
    if (button == BUTTON_3)
    {
        current_alarm_state = (current_alarm_state + 1) % ALARM_STATES;
        return;
    }

    switch (current_alarm_state)
    {
        case ALARM_ENABLED:
            if (button == BUTTON_2) 
                alarm_enabled = !alarm_enabled;
            break;

        case ALARM_HOUR:
            if (button == BUTTON_2) 
                alarm_time.tm_hour = (alarm_time.tm_hour + 1) % 24;
            break;

        case ALARM_MIN:
            if (button == BUTTON_2) 
                alarm_time.tm_min = (alarm_time.tm_min + 1) % 60;
            break;

        case ALARM_DAYS:
            if (button == BUTTON_1) 
            {
                alarm_day_toggle((WeekDay)alarm_time.tm_wday);
            }
            else if (button == BUTTON_2) 
            {
                alarm_time.tm_wday = (alarm_time.tm_wday + 1) % DAYS_IN_WEEK;
            }
            break;

        default:
            break;
    }
}