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
    CLKDIVbits.RCDIV = 0;      // No FRC division (Fcy = 16MHz)

    T1CON            = 0x0000; // Reset Timer 1 configuration
    T1CONbits.TCS    = 0;      // Internal clock (Fcy)
    T1CONbits.TCKPS  = 0b01;   // Prescaler 1:8

    TMR1             = 0;      // Reset timer counter
    PR1              = 1999;   // 2000 ticks * 0.5us = exactly 1ms
    
    IFS0bits.T1IF    = 0;      // Clear Timer 1 interrupt flag
    IEC0bits.T1IE    = 1;      // Enable Timer 1 interrupt

    T1CONbits.TON    = 1;      // Start Timer 1
}