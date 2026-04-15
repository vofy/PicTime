#ifndef STATE_H
#define	STATE_H

#include "../drivers/buttons.h"

typedef enum {
    STATE_CLOCK,
    STATE_STOPWATCH,
    STATE_ALARM,
    STATE_OPTIONS
} State;

void state_init(void);
void state_set_current(State next);
State state_get_current(void);
void state_handle_event(Key key);

#endif	/* STATE_H */