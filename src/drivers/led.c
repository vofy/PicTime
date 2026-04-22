#include <xc.h>
#include "led.h"

void led_init(void)
{
    TRISA = (TRISA & 0xFF80) | 0x0080; // RA0-RA6 as output, RA7 as input (shared with BUTTON_3)
    LATA &= 0xFF80;  
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