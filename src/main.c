#include <xc.h>

#include "drivers/controller.h"
#include "drivers/rtcc.h"
#include "drivers/lcd.h"
#include "drivers/buttons.h"
#include "drivers/interrupt.h"
#include "drivers/led.h"
#include "drivers/eeprom.h"

#include "core/state.h"
#include "core/clock.h"
#include "core/options.h"
#include "core/stopwatch.h"
#include "core/alarm.h"

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

int main(void)
{
    device_init();
    clock_init();
    
    while (1)
    {
        buttons_check_state();

        // Screen needs redraw
        switch(state_get_current()) {
            case STATE_CLOCK:
                clock_draw_screen();
                break;

            case STATE_STOPWATCH:
                if (stopwatch_state_get_current() == SW_RUN)
                    stopwatch_draw_screen();
                break;
            
            case STATE_OPTIONS:
                options_draw_screen();
                break;

            default:
                break;
        }
    }
    
    return 0;
}