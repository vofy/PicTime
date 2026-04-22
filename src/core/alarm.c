#include <xc.h>
#include <libpic30.h>

#include "alarm.h"
#include "../drivers/rtcc.h"
#include "../drivers/eeprom.h"
#include "../ui/views.h"

static AlarmSettings alarm_settings = {
    .enabled = false,
    .time = {0},
    .days_enabled = {
        [DAY_SUN] = false,
        [DAY_MON] = false, 
        [DAY_TUE] = false, 
        [DAY_WED] = false, 
        [DAY_THU] = false, 
        [DAY_FRI] = false, 
        [DAY_SAT] = false
    }
};

static AlarmState current_alarm_state = ALARM_ENABLED;
static bool alarm_signaling_triggered = false;
static WeekDay weekday_selected = DAY_MON;

void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void) 
{
    IFS3bits.RTCIF = 0;
    alarm_signaling_triggered = true; 
}

static bool alarm_is_valid(const AlarmSettings *settings)
{
    return settings->time.hour < 24 && settings->time.min < 60;
}

void alarm_init(void)
{
    AlarmSettings alarm_settings_temp;
    eeprom_read(0, &alarm_settings_temp, sizeof(alarm_settings_temp));
    
    // Only apply if the data read from EEPROM is valid
    if (alarm_is_valid(&alarm_settings_temp))
        alarm_settings = alarm_settings_temp;
}

WeekDay alarm_get_weekday_selected(void)
{
    return weekday_selected;
}

AlarmState alarm_get_state_current(void)
{
    return current_alarm_state;
}

const AlarmSettings* alarm_get_settings(void)
{
    return &alarm_settings;
}

bool alarm_is_day_enabled(WeekDay day)
{
    return alarm_settings.days_enabled[day];
}

bool alarm_is_enabled(void)
{
    return alarm_settings.enabled;
}

bool alarm_is_triggered(void)
{
    return alarm_signaling_triggered;
}

void alarm_set_triggered(bool state)
{
    alarm_signaling_triggered = state;
}

static void alarm_set_time_and_state(void)
{
    rtcc_set_alarm(&alarm_settings.time);
    rtcc_set_alarm_enabled(alarm_settings.enabled); // Enable/disable alarm flag
    eeprom_write(0, &alarm_settings, sizeof(alarm_settings));
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
                alarm_settings.enabled = !alarm_settings.enabled;
            break;

        case ALARM_HOUR:
            if (button == BUTTON_2) 
                alarm_settings.time.hour = (alarm_settings.time.hour + 1) % 24;
            break;

        case ALARM_MIN:
            if (button == BUTTON_2) 
                alarm_settings.time.min = (alarm_settings.time.min + 1) % 60;
            break;

        case ALARM_DAYS:
            if (button == BUTTON_1) 
            {
                weekday_selected = (weekday_selected + 1) % DAYS_ALL;
            }
            else if (button == BUTTON_2) 
            {
                alarm_settings.days_enabled[weekday_selected] = !alarm_settings.days_enabled[weekday_selected];
            }
            break;

        default:
            break;
    }

    alarm_set_time_and_state();
    
}