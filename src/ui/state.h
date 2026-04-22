#ifndef STATE_H
#define	STATE_H

typedef enum {
    STATE_CLOCK,
    STATE_OPTIONS,
    STATE_STOPWATCH,
    STATE_ALARM,
    STATE_STATES
} State;

void state_init(void);
void state_set_current(State next);
State state_get_current(void);
void state_handle_event(Button button);

#endif