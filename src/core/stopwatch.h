#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>
#include <stdbool.h>

#include "../drivers/buttons.h"

typedef enum {
    SW_IDLE,
    SW_RUN,
    SW_STOP,
    SW_LAP
} StopwatchState;

StopwatchState stopwatch_state_get_current(void);
void stopwatch_tick(void);
void stopwatch_handle_key(Button button);
uint32_t stopwatch_get_time(void);
bool stopwatch_is_running(void);

#endif