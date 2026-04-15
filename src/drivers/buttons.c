#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "buttons.h"
#include "../ui/state.h"

#define S3 PORTDbits.RD6
#define S6 PORTDbits.RD7
#define S5 PORTAbits.RA7
#define S4 PORTDbits.RD13

static bool buttons_state[4] = {false, false, false, false};   // debounced state
static bool buttons_last[4]  = {false, false, false, false};   // previous state
static uint8_t cnt[4] = {0};                                   // debounce counters

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
}

void buttons_check_state(void)
{
    for (int i = 0; i < 4; i++)
    {
        bool now = buttons_state[i];
        bool before = buttons_last[i];

        // detect rising edge (press event)
        if (!before && now)
        {
            state_handle_event((Button)(BUTTON_1 + i));
        }

        buttons_last[i] = now;
    }
}