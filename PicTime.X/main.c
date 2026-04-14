#include <xc.h>
#include "state.h"
#include "rtcc.h"
#include "lcd.h"
#include "screen.h"

#define ENTER_BTN   PORTDbits.RD6
#define ESC_BTN     PORTDbits.RD7
#define PREV_BTN    PORTAbits.RA7
#define NEXT_BTN    PORTDbits.RD13

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

static Key read_key()
{
    if (!ENTER_BTN) { while(!ENTER_BTN); return KEY_ENTER; }
    if (!ESC_BTN)   { while(!ESC_BTN);   return KEY_ESC; }
    if (!PREV_BTN)  { while(!PREV_BTN);  return KEY_PREV; }
    if (!NEXT_BTN)  { while(!NEXT_BTN);  return KEY_NEXT; }
    return KEY_NONE;
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

        if (IFS0bits.T1IF)
        {
            IFS0bits.T1IF = 0;

            switch (state_get_current())
            {
                case STATE_CLOCK:
                    draw_CLOCK();
                    break;

                case STATE_STOPWATCH_RUN:
                    draw_STOPWATCH();
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}