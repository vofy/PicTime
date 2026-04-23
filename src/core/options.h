
#ifndef OPTIONS_H
#define OPTIONS_H

#include "../drivers/buttons.h"

typedef enum {
    OPTIONS_DAY = 0,
    OPTIONS_MONTH,
    OPTIONS_YEAR,
    OPTIONS_HOUR,
    OPTIONS_MIN,
    OPTIONS_SEC,
    OPTIONS_STATES
} OptionsState;

OptionsState options_state_get_current(void);
void options_enter(void);
void options_set_time(struct tm *time);
void options_handle_key(Button button);
void options_draw_screen(void);

#endif