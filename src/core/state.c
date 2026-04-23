#include <stdbool.h>

#include "../drivers/buttons.h"

#include "../core/clock.h"
#include "../core/options.h"
#include "../core/stopwatch.h"
#include "../core/alarm.h"

#include "state.h"

static State state;

typedef struct {
    void (*enter)(void);
    void (*draw)(void);
    void (*handle)(Button button);
} StateHandler;


static StateHandler handlers[] =
{
    [STATE_CLOCK] =
    {
        .enter = NULL,
        .draw  = clock_draw_screen,
        .handle = NULL
    },
            
    [STATE_OPTIONS] =
    {
        .enter = options_enter,
        .draw  = options_draw_screen,
        .handle = options_handle_key
    },

    [STATE_STOPWATCH] =
    {
        .enter = NULL,
        .draw  = stopwatch_draw_screen,
        .handle = stopwatch_handle_key
    },

    [STATE_ALARM] =
    {
        .enter = alarm_enter,
        .draw  = alarm_draw_screen,
        .handle = alarm_handle_key
    }
};

void state_init(void)
{
    state = STATE_CLOCK;

    if (handlers[state].enter) handlers[state].enter();
    if (handlers[state].draw) handlers[state].draw();
}
void state_redraw_dynamic_views(void)
{
    switch(state) {
        case STATE_CLOCK:
            clock_draw_screen();
            break;

        case STATE_STOPWATCH:
            if (stopwatch_state_get_current() == SW_RUN)
                stopwatch_draw_screen();
            break;

        case STATE_OPTIONS:
            options_draw_screen();
            break;

        default:
            break;
    }
}

void state_set_current(State next)
{
    if (next == state)
        return;

    state = next;
    if (handlers[state].enter) handlers[state].enter();
    handlers[state].draw();
}

State state_get_current(void)
{
    return state;
}

void state_handle_event(Button button)
{
    if (alarm_is_triggered())
    {
        alarm_set_triggered(false);
        return;
    }
    
    if (button == BUTTON_4)
    {
        state = (state + 1) % STATE_STATES;
        if (handlers[state].enter)
            handlers[state].enter();
    }
    else
    {
        if (handlers[state].handle != NULL)
            handlers[state].handle(button);
    }
    
    handlers[state].draw();
}