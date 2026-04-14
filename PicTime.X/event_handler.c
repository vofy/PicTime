#include "state.h"
#include "rtcc.h"

State handle_CLOCK(Key key, State current)
{
    switch(key)
    {
        case KEY_PREV:  return STATE_OPTIONS;
        case KEY_NEXT:  return STATE_STOPWATCH;
        default:        return current;
    }
}

State handle_STOPWATCH(Key key, State current) {
    switch(key) {
        case KEY_PREV:  return STATE_CLOCK;
        case KEY_NEXT:  return STATE_ALARM;
        default:
            switch (current) {
                case STATE_STOPWATCH:
                    if (rtcc_stopwatch_is_running())
                        return STATE_STOPWATCH_RUN;
                    if (key == KEY_ENTER) {
                        rtcc_stopwatch_run();
                        return STATE_STOPWATCH_RUN;
                    }
                    break;
                case STATE_STOPWATCH_RUN:
                    if (key == KEY_ENTER) {
                        rtcc_stopwatch_stop();
                        return STATE_STOPWATCH_STOP;
                    }
                    else if (key == KEY_ESC) {
                        return STATE_STOPWATCH_LAP;
                    }
                    break;
                case STATE_STOPWATCH_LAP:
                    if (key == KEY_ENTER) {
                        return STATE_STOPWATCH_RUN;
                    }
                    break;
                case STATE_STOPWATCH_STOP:
                    if (key == KEY_ENTER) {
                        rtcc_stopwatch_run();
                        return STATE_STOPWATCH_RUN;
                    }
                    else if (key == KEY_ESC) {
                        rtcc_stopwatch_reset();
                        return STATE_STOPWATCH;
                    }
                default:
                    return current;
            }
            return current;
    }
}

State handle_ALARM(Key key, State current)
{
    switch(key)
    {
        case KEY_PREV:  return STATE_STOPWATCH;
        case KEY_NEXT:  return STATE_OPTIONS;
        default:        return current;
    }
}

State handle_OPTIONS(Key key, State current)
{
    switch(key)
    {
        case KEY_PREV:  return STATE_ALARM;
        case KEY_NEXT:  return STATE_CLOCK;
        default:        return current;
    }
}
