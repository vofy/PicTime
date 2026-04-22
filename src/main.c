#include <xc.h>
#include "drivers/rtcc.h"
#include "drivers/lcd.h"
#include "drivers/buttons.h"
#include "drivers/interrupts.h"
#include "drivers/led.h"
#include "drivers/eeprom.h"
#include "ui/state.h"
#include "ui/views.h"
#include "core/stopwatch.h"
#include "core/alarm.h"
#include "core/options.h"

// CONFIG1
#pragma config JTAGEN = OFF     // JTAG Port Enable (Disabled)
#pragma config ICS = PGx1       // Comm Channel Select (PGC1/PGD1)
#pragma config FWDTEN = OFF     // Watchdog Timer Enable (Disabled)
#pragma config WDTPS = PS32768  // Watchdog Timer Postscaler (1:32,768)

// CONFIG2
#pragma config IESO = ON        // Internal External Switch Over Mode (Enabled)
#pragma config FNOSC = FRCPLL   // Oscillator Select (Fast RC Oscillator with PLL)
#pragma config FCKSM = CSECMD   // Clock Switching and Monitor (Clock switching enabled, Fail-Safe Clock Monitor disabled)
#pragma config POSCMOD = NONE   // Primary Oscillator Select (Disabled)

static void init()
{
    lcd_init();
    rtcc_init();
    timer_init();
    led_init();
    eeprom_init();
    state_init();
    alarm_init();
}

int main(void)
{
    init();

    struct tm start_time = {
        .tm_year = 2026,
        .tm_mon  = 3,
        .tm_mday = 19,
        .tm_hour = 23,
        .tm_min  = 59,
        .tm_sec  = 55,
        .tm_wday = 3
    };

    rtcc_set_time(&start_time);
    
    while (1)
    {
        buttons_check_state();

        // Screen needs redraw
        switch(state_get_current()) {
            case STATE_CLOCK:
                draw_screen_clock();
                break;

            case STATE_STOPWATCH:
                if (stopwatch_state_get_current() == SW_RUN)
                    draw_screen_stopwatch();
                break;
            
            case STATE_OPTIONS:
                draw_screen_options();
                break;

            default:
                break;
        }
    }
        

    return 0;
}