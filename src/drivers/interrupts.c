#include <xc.h>

#include "../drivers/buttons.h"
#include "../core/stopwatch.h"

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;

    buttons_tick();
    stopwatch_tick();
}

void timer_init(void)
{
    T1CON = 0x0000;          // reset

    T1CONbits.TCKPS = 0b10;  // prescaler 1:64
    T1CONbits.TCS = 0;       // internal clock (Fcy)

    PR1 = 124;               // 1 ms period

    TMR1 = 0;

    IFS0bits.T1IF = 0;       // clear flag
    IEC0bits.T1IE = 1;       // ENABLE interrupt

    T1CONbits.TON = 1;       // start timer
}