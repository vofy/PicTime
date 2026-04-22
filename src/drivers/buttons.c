#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "buttons.h"
#include "../ui/state.h"

static bool buttons_state[4] = {false, false, false, false};   // debounced state
static bool buttons_last[4]  = {false, false, false, false};   // previous state
static uint8_t cnt[4] = {0};                                   // debounce counters
static uint16_t repeat_cnt[4] = {0};                           // counters for auto-repeat
static bool repeat_mode[4] = {false};                          // flag for repeat phase

void buttons_init(void)
{
    TRISDbits.TRISD6 = 1;  // S3
    TRISDbits.TRISD7 = 1;  // S6
    TRISAbits.TRISA7 = 1;  // S5
    TRISDbits.TRISD13 = 1; // S4
}

void buttons_tick(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        bool button_i_pressed = false;

        switch (i)
        {
            case 0: button_i_pressed = !S3; break;
            case 1: button_i_pressed = !S6; break;
            case 2: button_i_pressed = !S5; break;
            case 3: button_i_pressed = !S4; break;
        }

        if (button_i_pressed == buttons_state[i])
        {
            // stable ? count down
            if (cnt[i] > 0)
                cnt[i]--;
        }
        else
        {
            // unstable ? count up
            if (cnt[i] < 5)
            {
                cnt[i]++;
            }
            else
            {
                // stable change detected
                buttons_state[i] = button_i_pressed;
                cnt[i] = 0;
            }
        }
    }

    // Process auto-repeat for held buttons
    for (uint8_t i = 0; i < 4; i++)
    {
        if (buttons_state[i])
        {
            repeat_cnt[i]++;
            uint16_t threshold = repeat_mode[i] ? BUTTON_REPEAT_RATE : BUTTON_REPEAT_INITIAL;

            if (repeat_cnt[i] >= threshold)
            {
                buttons_last[i] = false; // Reset last state to trigger a new press event
                repeat_cnt[i] = 0;
                repeat_mode[i] = true;
            }
        }
        else
        {
            repeat_cnt[i] = 0;
            repeat_mode[i] = false;
        }
    }
}

void buttons_check_state(void)
{
    for (int i = 0; i < 4; i++)
    {
        bool now = buttons_state[i];
        bool before = buttons_last[i];
        
        // detect press event
        if (!before && now)
        {
            state_handle_event((Button)(BUTTON_1 + i));
        }

        buttons_last[i] = now;
    }
}