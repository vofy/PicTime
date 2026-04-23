#ifndef RTCC_H
#define	RTCC_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t hour;
    uint8_t min;
} HrMin;

void rtcc_init(void);
void rtcc_get_time(struct tm *t);
void rtcc_set_time(struct tm *t);
void rtcc_set_alarm(const HrMin *t);
void rtcc_set_alarm_enabled(bool enabled);

#endif