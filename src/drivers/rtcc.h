#ifndef RTCC_H
#define	RTCC_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t hour;
    uint8_t min;
} HrMin;

extern const char* weekday_strings[7];

void rtcc_init(void);
void rtcc_get_time(struct tm *t);
void rtcc_set_time(struct tm *t);
void rtcc_set_alarm(const HrMin *t);
void rtcc_set_alarm_enabled(bool enabled);
const char *rtcc_weekday_str(struct tm *t);
const int rtcc_week_number(struct tm *t);

#endif