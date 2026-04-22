#include <xc.h>

#include "../drivers/buttons.h"
#include "../core/stopwatch.h"
#include "../core/alarm.h"
#include "../drivers/led.h"

void alarm_blink_service(void)
{
    static uint16_t blink_cnt = 0;
    
    if (alarm_is_triggered())
    {
        if (++blink_cnt >= 200) // Toggle every 200ms
        {
            blink_cnt = 0;
            for (int i = 0; i < LED_ALL; i++) led_toggle(i);
            LATDbits.LATD0 ^= 1; // Pulse buzzer on RD0
        }
    }
    else
    {
        blink_cnt = 0;
    }
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;

    buttons_tick();
    stopwatch_tick();
    alarm_tick();
    
    alarm_blink_service();
}

void timer_init(void)
{
    T1CON            = 0x0000; // Reset Timer 1 configuration
    T1CONbits.TCS    = 0;      // Internal clock (Fcy)
    T1CONbits.TCKPS  = 0b01;   // Prescaler 1:8

    TMR1             = 0;      // Reset timer counter
    PR1              = 1999;   // 2000 ticks * 0.5us = exactly 1ms
    
    IFS0bits.T1IF    = 0;      // Clear Timer 1 interrupt flag
    IEC0bits.T1IE    = 1;      // Enable Timer 1 interrupt

    T1CONbits.TON    = 1;      // Start Timer 1
}