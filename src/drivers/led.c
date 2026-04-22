#include <xc.h>
#include "led.h"

void led_init(void)
{
    TRISA &= ~0x00FF; // RA0-RA7 as output (D3-D10)
    LATA &= 0xFF00;  
}

void led_set(Led led, bool state)
{
    if (led >= LED_ALL) return; 

    if (state)
        LATA |= (1 << led); // OR
    else
        LATA &= ~(1 << led); // AND
}

void led_toggle(Led led)
{
    if (led >= LED_ALL) return;

    LATA ^= (1 << led); // XOR
}

void led_set_all(bool state)
{
    if (state)
        LATA |= 0x00FF; // Set RA0-RA7
    else
        LATA &= ~0x00FF; // Clear RA0-RA7
}