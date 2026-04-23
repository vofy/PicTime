#include <xc.h>

#include "controller.h"
#include "led.h"
#include "buttons.h"
#include "lcd.h"
#include "eeprom.h"
#include "rtcc.h"
#include "interrupt.h"

#include "../core/clock.h"
#include "../core/alarm.h"
#include "../core/state.h"

void device_init(void)
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0xFFFF;

    led_init();
    buttons_init();
    lcd_init();
    eeprom_init();
    rtcc_init();
    
    clock_init();
    timer_init();
    alarm_init();
    
    state_init();
}