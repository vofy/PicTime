#include <xc.h>
#include "drivers/rtcc.h"
#include "drivers/lcd.h"
#include "drivers/buttons.h"
#include "ui/state.h"
#include "ui/views.h"
#include "core/stopwatch.h"

_CONFIG1 (0x3F7F)
_CONFIG2 (0xF99F)

static void led_init()
{
    TRISAbits.TRISA0 = 0;
}

static void timer_init()
{
    T1CON = 0x0020;     // Fosc/2, prescaler 1:64
    PR1 = 31250;        // 500 ms
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 0;
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
        Key key = read_key();
        
        if (key != KEY_NONE)
            state_handle_event(key);

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