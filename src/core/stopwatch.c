#include <xc.h>
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "stopwatch.h"
#include "../drivers/buttons.h"
#include "../drivers/lcd.h"

static StopwatchState stopwatch_state = SW_IDLE;

static volatile uint32_t elapsed_ms = 0;
static volatile bool running = false;

StopwatchState stopwatch_state_get_current(void)
{
    return stopwatch_state;
}

void stopwatch_tick(void)
{
    if (running)
        elapsed_ms++;
}

void stopwatch_handle_key(Button button)
{
    switch (stopwatch_state)
    {
        case SW_IDLE:
            if (button == BUTTON_1)
            {
                running = true;
                stopwatch_state = SW_RUN;
            }
            break;

        case SW_RUN:
            if (button == BUTTON_2)
            {
                running = false;
                stopwatch_state = SW_STOP;
            }
            else if (button == BUTTON_3)
                stopwatch_state = SW_LAP;
            break;

        case SW_LAP:
            if (button == BUTTON_1)
                stopwatch_state = SW_RUN;
            else if (button == BUTTON_2)
                stopwatch_state = SW_STOP;
            else if (button == BUTTON_3)
                stopwatch_state = SW_LAP;
            break;

        case SW_STOP:
            if (button == BUTTON_1)
            {
                running = true;
                stopwatch_state = SW_RUN;
            }
            else if (button == BUTTON_2)
            {
                elapsed_ms = 0;
                stopwatch_state = SW_IDLE;
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

void stopwatch_draw_screen(void)
{
    char lineBuffer[17];
    
    uint32_t time = stopwatch_get_time();
    char state_str[7] = "";
    
    switch(stopwatch_state)
    {
        case SW_RUN:
            strcpy(state_str, " [RUN]");
            break;
        case SW_LAP:
            strcpy(state_str, " [LAP]");
            break;
        case SW_STOP:
            strcpy(state_str, "[STOP]");
            break;
        default:
            break;
    }
    sprintf(lineBuffer, "Stopwatch %s", state_str);
    lcd_write_line(0, lineBuffer);

    uint32_t hours   =  time / 3600000UL;
    uint32_t minutes = (time % 3600000UL) / 60000UL;
    uint32_t seconds = (time % 60000UL) / 1000UL;
    uint32_t centis  = (time % 1000UL) / 10UL;

    sprintf(lineBuffer, "%02lu:%02lu:%02lu.%02lu",
        hours, minutes, seconds, centis);
    
    lcd_write_line(1, lineBuffer);
}