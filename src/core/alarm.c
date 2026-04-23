#include <xc.h>
#include <stdio.h>

#include "alarm.h"
#include "clock.h"
#include "../drivers/rtcc.h"
#include "../drivers/eeprom.h"
#include "../drivers/led.h"
#include "../drivers/lcd.h"

static AlarmSettings alarm_settings = {
    .magic = ALARM_MAGIC_VALUE,
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

static AlarmState alarm_state = ALARM_ENABLED;
static bool alarm_triggered = false;
static WeekDay weekday_selected = DAY_MON;

void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void) 
{
    IFS3bits.RTCIF = 0;
    alarm_set_triggered(true); 
}

void alarm_init(void)
{
    AlarmSettings alarm_settings_temp = {0};
    eeprom_read(ALARM_EEPROM_ADDR, &alarm_settings_temp, sizeof(alarm_settings_temp));

    if (alarm_settings_temp.magic == ALARM_MAGIC_VALUE)
        alarm_settings = alarm_settings_temp;
    else
        eeprom_write(ALARM_EEPROM_ADDR, &alarm_settings, sizeof(alarm_settings));

    rtcc_set_alarm(&alarm_settings.time);
    rtcc_set_alarm_enabled(alarm_settings.enabled);
}

WeekDay alarm_get_weekday_selected(void)
{
    return weekday_selected;
}

AlarmState alarm_get_state_current(void)
{
    return alarm_state;
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
    return alarm_triggered;
}

void alarm_set_triggered(bool state)
{
    struct tm current_time;
    rtcc_get_time(&current_time);

    bool day_enabled = alarm_settings.days_enabled[(WeekDay)current_time.tm_wday];

    if (alarm_settings.enabled && day_enabled)
        alarm_triggered = state;
    else
        alarm_triggered = false;
}

void alarm_enter(void)
{
    alarm_state = ALARM_ENABLED;
    weekday_selected = DAY_MON;
}

void alarm_day_toggle(WeekDay day)
{
    if (day < DAYS_ALL)
        alarm_settings.days_enabled[day] = !alarm_settings.days_enabled[day];
}

void alarm_draw_screen(void)
{
    char alarm_en[11];
    char hr[6];
    char min[6];
    char day_en[16];
    char lineBuffer[17];

    AlarmState state = alarm_state;
    WeekDay selected = weekday_selected;
    const char* day_state_str = alarm_is_day_enabled(selected) ? "ON" : "OFF";

    sprintf(alarm_en, (state == ALARM_ENABLED) ? "<%s>" : "%s", alarm_settings.enabled ? "ENABLED" : "DISABLED");
    sprintf(hr,       (state == ALARM_HOUR) ? "<%02d>" : "%02d", alarm_settings.time.hour);
    sprintf(min,      (state == ALARM_MIN) ? "<%02d>" : "%02d", alarm_settings.time.min);
    sprintf(day_en,   (state == ALARM_DAYS) ? "<%s-%s>" : "%s-%s", clock_get_weekday_name(selected), day_state_str);

    sprintf(lineBuffer, "Alarm %-10s", alarm_en);
    lcd_write_line(0, lineBuffer);

    sprintf(lineBuffer, "%s:%s %-11s", hr, min, day_en);
    lcd_write_line(1, lineBuffer);
}

void alarm_set_time_and_state(void)
{
    rtcc_set_alarm(&alarm_settings.time);
    rtcc_set_alarm_enabled(alarm_settings.enabled); // Enable/disable alarm flag
    eeprom_write(ALARM_EEPROM_ADDR, &alarm_settings, sizeof(alarm_settings));
}

void alarm_blink_led(Led led)
{
    static unsigned int blink_cnt = 0;
    
    if (alarm_is_triggered())
    {
        if (++blink_cnt >= 200) // Toggle every 200ms
        {
            blink_cnt = 0;
            led_toggle(ALARM_LED);
        }
    }
    else
        blink_cnt = 0;
}

void alarm_tick(void)
{
    static unsigned int alarm_triggered_time = 0;
    
    if(alarm_triggered && alarm_triggered_time < ALARM_SNOOZE_TIME)
    {
        alarm_blink_led(ALARM_LED);
        alarm_triggered_time++;
    }
    else
    {
        led_set(ALARM_LED, false);
        alarm_triggered = false;
        alarm_triggered_time = 0;
    }
}

void alarm_handle_key(Button button)
{
    bool changed = false;

    if (alarm_is_triggered())
    {
        if (button == BUTTON_1) // Snooze for 5 minutes
        {
            alarm_triggered = false;
            led_set_all(false);
            LATDbits.LATD0 = 0;
            return;
        }
    }

    if (button == BUTTON_3)
    {
        alarm_state = (alarm_state + 1) % ALARM_STATES;
        return;
    }

    switch (alarm_state)
    {
        case ALARM_ENABLED:
            if (button == BUTTON_2) {
                alarm_settings.enabled = !alarm_settings.enabled;
                changed = true;
            }
            break;

        case ALARM_HOUR:
            if (button == BUTTON_2) {
                alarm_settings.time.hour = (alarm_settings.time.hour + 1) % 24;
                changed = true;
            }
            break;

        case ALARM_MIN:
            if (button == BUTTON_2) {
                alarm_settings.time.min = (alarm_settings.time.min + 1) % 60;
                changed = true;
            }
            break;

        case ALARM_DAYS:
            if (button == BUTTON_1) 
                weekday_selected = (weekday_selected + 1) % DAYS_ALL;
            else if (button == BUTTON_2) 
            {
                alarm_settings.days_enabled[weekday_selected] = !alarm_settings.days_enabled[weekday_selected];
                changed = true;
            }
            break;

        default:
            break;
    }

    if (changed)
    {
        alarm_set_time_and_state();
    }
}