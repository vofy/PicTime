#include <xc.h>
#include <stdint.h>
#include <time.h>

#include "options.h"
#include "../drivers/buttons.h"
#include "../drivers/rtcc.h"

static OptionsState current_option_state = OPTIONS_YEAR;

OptionsState options_state_get_current(void)
{
    return current_option_state;
}

void options_handle_key(Button button)
{
    if (button == BUTTON_3)
    {
        current_option_state = (current_option_state + 1) % OPTIONS_STATES;
        return;
    }

    if (button == BUTTON_2)
    {
        struct tm time;
        rtcc_get_time(&time);

        switch (current_option_state)
        {
            case OPTIONS_YEAR:
                time.tm_year++;
                if (time.tm_year > 200) time.tm_year = 100;
                break;
                
            case OPTIONS_MONTH:
                time.tm_mon = (time.tm_mon + 1) % 12;
                break;
                
            case OPTIONS_DAY:
                time.tm_mday = (time.tm_mday % 31) + 1;
                break;
                
            case OPTIONS_HOUR:
                time.tm_hour = (time.tm_hour + 1) % 24;
                break;
                
            case OPTIONS_MIN:
                time.tm_min = (time.tm_min + 1) % 60;
                break;
                
            case OPTIONS_SEC:
                time.tm_sec = 0;
                break;
                
            default:
                break;
        }
        
        rtcc_set_time(&time);
    }
}