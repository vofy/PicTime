#ifndef EVENT_HANDLER_H
#define	EVENT_HANDLER_H

State handle_CLOCK(Key key, State current);
State handle_STOPWATCH(Key key, State current);
State handle_ALARM(Key key, State current);
State handle_OPTIONS(Key key, State current);

#endif	/* EVENT_HANDLER_H */

