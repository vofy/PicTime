#ifndef RTCC_H
#define	RTCC_H

void initRtcc();
void rtcc_get_tm(struct tm *t);
void rtcc_set_tm(const struct tm *t);
const char *rtcc_weekday_str(const struct tm *t);
int rtcc_week_number(const struct tm *t);

#endif	/* RTCC_H */