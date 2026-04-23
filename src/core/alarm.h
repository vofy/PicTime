#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>
#include <stdbool.h>
#include "../drivers/buttons.h"
#include "../drivers/rtcc.h"

#define ALARM_LED LED_1
#define ALARM_SNOOZE_TIME 60000
#define ALARM_MAGIC_VALUE 0xCAFE
#define ALARM_EEPROM_ADDR 0x00

typedef enum {
    ALARM_ENABLED = 0,
    ALARM_HOUR,
    ALARM_MIN,
    ALARM_DAYS,
    ALARM_STATES
} AlarmState;

typedef enum {
    DAY_SUN = 0,
    DAY_MON,
    DAY_TUE,
    DAY_WED,
    DAY_THU,
    DAY_FRI,
    DAY_SAT,
    DAYS_ALL
} WeekDay;

typedef struct {
    uint16_t magic;
    bool enabled;
    HrMin time;
    bool days_enabled[DAYS_ALL];
} AlarmSettings;

void alarm_init(void);
WeekDay alarm_get_weekday_selected(void);
AlarmState alarm_get_state_current(void);
const AlarmSettings* alarm_get_settings(void);
bool alarm_is_day_enabled(WeekDay day);
bool alarm_is_enabled(void);
bool alarm_is_triggered(void);
void alarm_set_triggered(bool state);
void alarm_enter(void);
void alarm_day_toggle(WeekDay day);
void alarm_draw_screen(void);
void alarm_set_time_and_state(void);
void alarm_tick(void);
void alarm_handle_key(Button button);

#endif