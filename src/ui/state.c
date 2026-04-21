#include <stdbool.h>

#include "../drivers/buttons.h"
#include "../core/stopwatch.h"
#include "../core/alarm.h"
#include "../core/options.h"
#include "state.h"
#include "views.h"

static State current_state;

typedef struct {
    void (*draw)(void);
    void (*handle)(Button button);
} StateHandler;

static void clock_handle_key(Button button) {};

static StateHandler handlers[] =
{
    [STATE_CLOCK] =
    {
        .draw  = draw_screen_clock,
        .handle = clock_handle_key
    },

    [STATE_STOPWATCH] =
    {
        .draw  = draw_screen_stopwatch,
        .handle = stopwatch_handle_key
    },

    [STATE_ALARM] =
    {
        .draw  = draw_screen_alarm,
        .handle = alarm_handle_key
    },

    [STATE_OPTIONS] =
    {
        .draw  = draw_screen_options,
        .handle = options_handle_key
    }
};

void state_init(void)
{
    current_state = STATE_CLOCK;

    handlers[current_state].draw();
}

void state_set_current(State next)
{
    if (next == current_state)
        return;

    current_state = next;
    handlers[current_state].draw();
}

State state_get_current(void)
{
    return current_state;
}

void state_handle_event(Button button)
{    
    if (button == BUTTON_4)
        current_state = (current_state + 1) % STATE_STATES;
    else
        handlers[current_state].handle(button);
    
    handlers[current_state].draw();
}