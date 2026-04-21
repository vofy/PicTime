
#ifndef OPTIONS_H
#define OPTIONS_H

#include "../drivers/buttons.h"

typedef enum {
    OPTIONS_YEAR = 0,
    OPTIONS_MONTH,
    OPTIONS_DAY,
    OPTIONS_HOUR,
    OPTIONS_MIN,
    OPTIONS_SEC,
    OPTIONS_STATES
} OptionsState;

OptionsState options_state_get_current(void);
void options_handle_key(Button button);

#endif