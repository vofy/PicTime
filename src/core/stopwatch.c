#define FCY 8000000

#include <xc.h>
#include <libpic30.h>
#include "stopwatch.h"

static StopwatchState current_state = SW_IDLE;

static volatile uint32_t elapsed_ms = 0;
static volatile bool running = false;

void __attribute__ ( ( interrupt, no_auto_psv ) ) _T1Interrupt ( )
{
    elapsed_ms++;
    IFS0bits.T1IF = 0;
}

StopwatchState stopwatch_state_get_current()
{
    return current_state;
}

void stopwatch_tick_1ms(void)
{
    if (running)
    {
        __builtin_disi(0x3FFF);
        elapsed_ms++;
        __builtin_disi(0x0000);
    }
}

void stopwatch_state_handle_key(Key key)
{
    switch (current_state)
    {
        case SW_IDLE:
            if (key == KEY_ENTER)
            {
                running = true;
                current_state = SW_RUN;
            }
            break;

        case SW_RUN:
            if (key == KEY_ENTER)
            {
                running = false;
                current_state = SW_STOP;
            }
            else if (key == KEY_ESC)
            {
                current_state = SW_LAP;
            }
            break;

        case SW_LAP:
            if (key == KEY_ENTER)
                current_state = SW_RUN;
            break;

        case SW_STOP:
            if (key == KEY_ENTER)
            {
                running = true;
                current_state = SW_RUN;
            }
            else if (key == KEY_ESC)
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