#include <stdbool.h>

#include "../drivers/buttons.h"
#include "../core/stopwatch.h"
#include "state.h"
#include "views.h"

static State current_state;

static State handle_clock(Button button)
{
    if (button == BUTTON_4)
        return STATE_STOPWATCH;

    return STATE_CLOCK;
}

static State handle_stopwatch(Button button)
{
    switch (button)
    {
        case BUTTON_4:
            return STATE_ALARM;

        case BUTTON_1:
        case BUTTON_2:
            stopwatch_state_handle_key(button);
            break;

        default:
            break;
    }

    return STATE_STOPWATCH;
}

static State handle_alarm(Button button)
{
    if (button == BUTTON_4)
        return STATE_OPTIONS;

    return STATE_ALARM;
}

static State handle_options(Button button)
{

    if (button == BUTTON_4)
        return STATE_CLOCK;

    return STATE_OPTIONS;
}

typedef struct {
    void (*draw)(void);
    State (*handle)(Button button);
} StateHandler;

static StateHandler handlers[] =
{
    [STATE_CLOCK] =
    {
        .draw  = draw_screen_clock,
        .handle = handle_clock
    },

    [STATE_STOPWATCH] =
    {
        .draw  = draw_screen_stopwatch,
        .handle = handle_stopwatch
    },

    [STATE_ALARM] =
    {
        .draw  = draw_screen_alarm,
        .handle = handle_alarm
    },

    [STATE_OPTIONS] =
    {
        .draw  = draw_screen_options,
        .handle = handle_options
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
    State next = handlers[current_state].handle(button);

    if (next != current_state)
        state_set_current(next);
    
    handlers[current_state].draw();
}