#include <xc.h>
#include "drivers/rtcc.h"
#include "drivers/lcd.h"
#include "drivers/buttons.h"
#include "drivers/interrupts.h"
#include "ui/state.h"
#include "ui/views.h"
#include "core/stopwatch.h"

_CONFIG1 (0x3F7F)
_CONFIG2 (0xF99F)

static void led_init()
{
    TRISAbits.TRISA0 = 0;
}

static void init()
{
    lcd_init();
    rtcc_init();
    timer_init();
    led_init();
    state_init();
}

int main(void)
{
    init();

    struct tm time = {
        .tm_year = 2026,
        .tm_mon  = 3,
        .tm_mday = 19,
        .tm_hour = 23,
        .tm_min  = 59,
        .tm_sec  = 55,
        .tm_wday = 3
    };

    rtcc_set_time(&time);
    
    while (1)
    {
        buttons_check_state();

        // Screen needs redraw
        switch(state_get_current()) {
            case STATE_CLOCK:
                draw_screen_clock();
                break;

            case STATE_STOPWATCH: {
                if (stopwatch_state_get_current() == SW_RUN)
                    draw_screen_stopwatch();
                break;
            }

            default:
                break;
        }
    }

    return 0;
}