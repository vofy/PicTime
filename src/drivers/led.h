#ifndef LED_H
#define LED_H

#include <stdbool.h>

typedef enum {
    LED_1 = 0, // RA0 (D3)
    LED_2,     // RA1 (D4)
    LED_3,     // RA2 (D5)
    LED_4,     // RA3 (D6)
    LED_5,     // RA4 (D7)
    LED_6,     // RA5 (D8)
    LED_7,     // RA6 (D9)
    LED_8,     // RA7 (D10)
    LED_ALL
} Led;

void led_init(void);
void led_set(Led led, bool state);
void led_toggle(Led led);
void led_set_all(bool state);

#endif