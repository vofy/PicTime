#ifndef RTCC_H
#define	RTCC_H

#include <time.h>

void rtcc_init(void);
void rtcc_get_time(struct tm *t);
void rtcc_set_time(struct tm *t);
const char *rtcc_weekday_str(struct tm *t);
const int rtcc_week_number(struct tm *t);

#endif