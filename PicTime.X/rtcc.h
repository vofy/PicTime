#ifndef RTCC_H
#define	RTCC_H

#include <time.h>
#include <stdbool.h>

void rtcc_stopwatch_run();
void rtcc_stopwatch_stop();
void rtcc_stopwatch_reset();
time_t rtcc_stopwatch_time();
bool rtcc_stopwatch_is_running();
void rtcc_init(void);
void rtcc_get_time(struct tm *t);
void rtcc_set_time(struct tm *t);
const char *rtcc_weekday_str(struct tm *t);
const int rtcc_week_number(struct tm *t);

#endif	/* RTCC_H */