#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include <time.h>

void clock_init(void);
void clock_set_time(struct tm *t);
const char *clock_get_weekday_str(struct tm *t);
const char *clock_get_weekday_name(int day_index);
int clock_get_week_number(struct tm *t);
void clock_draw_screen(void);

#endif