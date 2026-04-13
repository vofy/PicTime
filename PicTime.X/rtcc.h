#ifndef RTCC_H
#define	RTCC_H

void rtcc_init();
void rtcc_get_time(struct tm *t);
void rtcc_set_time(const struct tm *t);
const char *rtcc_weekday_str(const struct tm *t);
int rtcc_week_number(const struct tm *t);

#endif	/* RTCC_H */