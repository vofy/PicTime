#include "state.h"
#include "screen.h"
#include "event_handler.h"

typedef struct {
    void (*draw)(void);
    State (*handle_event)(Key key, State current);
} Screen;

static volatile State current_state = STATE_CLOCK;

static Screen state[STATE_MAX] = {
    [STATE_CLOCK] = { draw_CLOCK, handle_CLOCK },

    // Stopwatch
    [STATE_STOPWATCH]      = { draw_STOPWATCH, handle_STOPWATCH },
    [STATE_STOPWATCH_RUN]  = { draw_STOPWATCH, handle_STOPWATCH },
    [STATE_STOPWATCH_LAP]  = { draw_STOPWATCH, handle_STOPWATCH },
    [STATE_STOPWATCH_STOP] = { draw_STOPWATCH, handle_STOPWATCH },

    // Alarm
    [STATE_ALARM]         = { draw_ALARM, handle_ALARM },
    [STATE_ALARM_ENABLED] = { draw_ALARM, handle_ALARM },
    [STATE_ALARM_HOUR]    = { draw_ALARM, handle_ALARM },
    [STATE_ALARM_MIN]     = { draw_ALARM, handle_ALARM },
    [STATE_ALARM_VOLUME]  = { draw_ALARM, handle_ALARM },

    // Options
    [STATE_OPTIONS]            = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_TIME]       = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_TIME_HOUR]  = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_TIME_MIN]   = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_TIME_SEC]   = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_DATE]       = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_DATE_DAY]   = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_DATE_MONTH] = { draw_OPTIONS, handle_OPTIONS },
    [STATE_OPTIONS_DATE_YEAR]  = { draw_OPTIONS, handle_OPTIONS }
};

void state_init()
{
    state_set_current(STATE_CLOCK);
}
void state_set_current(State next)
{
    current_state = next;

    if (state[current_state].draw)
        state[current_state].draw();

    if (state[current_state].handle_event)
        state[current_state].handle_event(KEY_NONE, current_state);
}

State state_get_current()
{
    return current_state;
}

void state_handle_event(Key key)
{
    if (key == KEY_NONE || !state[current_state].handle_event)
        return;

    state_set_current(state[current_state].handle_event(key, current_state));
}