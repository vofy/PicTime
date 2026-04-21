#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "../drivers/buttons.h"

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
    DAYS_IN_WEEK
} WeekDay;

extern const char* const weekday_strings[DAYS_IN_WEEK];
AlarmState alarm_state_get_current(void);
struct tm alarm_get_time(void);
bool alarm_is_enabled(void);
bool alarm_is_day_enabled(WeekDay day);
void alarm_day_toggle(WeekDay day);
void alarm_handle_key(Button button);

#endif