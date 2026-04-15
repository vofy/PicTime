#include <stdbool.h>

#include "state.h"
#include "views.h"
#include "../core/stopwatch.h"
#include "../core/options.h"

static State current_state = STATE_CLOCK;

typedef struct {
    void (*enter)(void);
    void (*draw)(void);
    State (*handle)(Key key);
} StateHandler;

static void enter_clock(void)     {}
static void enter_stopwatch(void) {}
static void enter_alarm(void)     {}
static void enter_options(void)   {}

static State handle_clock(Key key)
{
    switch (key)
    {
        case KEY_PREV: return STATE_OPTIONS;
        case KEY_NEXT: return STATE_STOPWATCH;
        default:       return STATE_CLOCK;
    }
}

static State handle_stopwatch(Key key)
{
    switch (key)
    {
        case KEY_PREV: return STATE_CLOCK;
        case KEY_NEXT: return STATE_ALARM;

        default:
            stopwatch_state_handle_key(key);
            return STATE_STOPWATCH;
    }
}

static State handle_alarm(Key key)
{
    switch (key)
    {
        case KEY_PREV: return STATE_STOPWATCH;
        case KEY_NEXT: return STATE_OPTIONS;
        default:       return STATE_ALARM;
    }
}

static State handle_options(Key key)
{
    switch (key)
    {
        case KEY_PREV: return STATE_ALARM;
        case KEY_NEXT: return STATE_CLOCK;
        default:       return STATE_OPTIONS;
    }
}

static StateHandler handlers[] =
{
    [STATE_CLOCK] =
    {
        .enter = enter_clock,
        .draw  = draw_screen_clock,
        .handle = handle_clock
    },

    [STATE_STOPWATCH] =
    {
        .enter = enter_stopwatch,
        .draw  = draw_screen_stopwatch,
        .handle = handle_stopwatch
    },

    [STATE_ALARM] =
    {
        .enter = enter_alarm,
        .draw  = draw_screen_alarm,
        .handle = handle_alarm
    },

    [STATE_OPTIONS] =
    {
        .enter = enter_options,
        .draw  = draw_screen_options,
        .handle = handle_options
    }
};

void state_init(void)
{
    current_state = STATE_CLOCK;

    if (handlers[current_state].enter)
        handlers[current_state].enter();

    if (handlers[current_state].draw)
        handlers[current_state].draw();
}

void state_set_current(State next)
{
    if (next == current_state)
        return;

    current_state = next;

    if (handlers[current_state].enter)
        handlers[current_state].enter();

    if (handlers[current_state].draw)
        handlers[current_state].draw();
}

State state_get_current(void)
{
    return current_state;
}

void state_handle_event(Key key)
{
    if (key == KEY_NONE)
        return;

    if (!handlers[current_state].handle)
        return;

    State next = handlers[current_state].handle(key);

    if (next != current_state)
    {
        state_set_current(next);
    }
}