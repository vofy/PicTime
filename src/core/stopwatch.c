#include <xc.h>
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>

#include "stopwatch.h"
#include "../drivers/buttons.h"
#include "../ui/views.h"

static StopwatchState current_state = SW_IDLE;

static volatile uint32_t elapsed_ms = 0;
static volatile bool running = false;

StopwatchState stopwatch_state_get_current(void)
{
    return current_state;
}

void stopwatch_tick(void)
{
    if (running)
        elapsed_ms++;
}

void stopwatch_handle_key(Button button)
{
    switch (current_state)
    {
        case SW_IDLE:
            if (button == BUTTON_1)
            {
                running = true;
                current_state = SW_RUN;
            }
            break;

        case SW_RUN:
            if (button == BUTTON_2)
            {
                running = false;
                current_state = SW_STOP;
            }
            else if (button == BUTTON_3)
                current_state = SW_LAP;
            break;

        case SW_LAP:
            if (button == BUTTON_1)
                current_state = SW_RUN;
            else if (button == BUTTON_2)
                current_state = SW_STOP;
            else if (button == BUTTON_3)
                current_state = SW_LAP;
            break;

        case SW_STOP:
            if (button == BUTTON_1)
            {
                running = true;
                current_state = SW_RUN;
            }
            else if (button == BUTTON_2)
            {
                elapsed_ms = 0;
                current_state = SW_IDLE;
            }
            break;
    }
}

uint32_t stopwatch_get_time(void)
{
    return elapsed_ms;
}

bool stopwatch_is_running(void)
{
    return running;
}