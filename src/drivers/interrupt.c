#include <xc.h>
#include <stdbool.h>

#include "interrupt.h"
#include "../drivers/buttons.h"
#include "../core/stopwatch.h"
#include "../core/alarm.h"
#include "../drivers/led.h"

static bool T1_interrupt = false;

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
    T1_interrupt = true;

    buttons_debounce_tick();
    stopwatch_tick();
    alarm_tick();
}

void timer_init(void)
{
    T1CON            = 0x0000; // Reset timer configuration
    T1CONbits.TCS    = 0;      // Internal clock (Fcy)
    T1CONbits.TCKPS  = 0b01;   // Prescaler 1:8

    TMR1             = 0;      // Reset timer counter
    PR1              = 1999;   // 1ms
    
    IFS0bits.T1IF    = 0;      // Clear interrupt flag
    IEC0bits.T1IE    = 1;      // Enable interrupt

    T1CONbits.TON    = 1;      // Start timer
}

void timer_clear_interrupt_flag(void)
{
    T1_interrupt = false;
}

bool timer_is_interrupt_active(void)
{
    return T1_interrupt;
}