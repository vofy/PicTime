#include <xc.h>
#include <stdlib.h>
#include "rtcc.h"

static int bcd2dec(unsigned int bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static int dec2bcd(int dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

void rtcc_init(void)
{
    // Enable secondary oscillator
    CLKDIV = 0;
    __builtin_write_OSCCONL(0x02);
    while(!OSCCONbits.SOSCEN);

    // Enable RTCC
    __builtin_write_RTCWEN();
    RCFGCALbits.RTCEN = 1;
    RCFGCALbits.RTCWREN = 0;

    // Enable RTCC Interrupt
    IFS3bits.RTCIF = 0;
    IEC3bits.RTCIE = 1;

    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
}

void rtcc_get_time(struct tm *t)
{
    unsigned int val;

    // Seconds + minutes
    RCFGCALbits.RTCPTR = 0b00;
    val = RTCVAL;
    t->tm_sec = bcd2dec(val & 0xFF);
    t->tm_min = bcd2dec((val >> 8) & 0xFF);

    // Weekday + hours
    RCFGCALbits.RTCPTR = 0b01;
    val = RTCVAL;
    t->tm_hour = bcd2dec(val & 0xFF);
    t->tm_wday = bcd2dec((val >> 8) & 0xFF);

    // Day + month
    RCFGCALbits.RTCPTR = 0b10;
    val = RTCVAL;
    t->tm_mday = bcd2dec(val & 0xFF);
    t->tm_mon  = bcd2dec((val >> 8) & 0xFF);

    // Year
    RCFGCALbits.RTCPTR = 0b11;
    val = RTCVAL;
    t->tm_year = bcd2dec(val & 0xFF) + 100;

    t->tm_isdst = -1;
    
    mktime(t);
}

void rtcc_set_time(struct tm *t)
{
    __builtin_write_RTCWEN();

    // Seconds + minutes
    RCFGCALbits.RTCPTR = 0b00;
    RTCVAL = (dec2bcd(t->tm_min) << 8) | dec2bcd(t->tm_sec);

    // Weekday + hours
    RCFGCALbits.RTCPTR = 0b01;
    RTCVAL = (dec2bcd(t->tm_wday) << 8) | dec2bcd(t->tm_hour);

    // Day + month
    RCFGCALbits.RTCPTR = 0b10;
    RTCVAL = (dec2bcd(t->tm_mon) << 8) | dec2bcd(t->tm_mday);

    // Year
    RCFGCALbits.RTCPTR = 0b11;
    RTCVAL = dec2bcd((t->tm_year + 1900) % 100);

    RCFGCALbits.RTCWREN = 0;
}

void rtcc_set_alarm(const HrMin *t)
{
    __builtin_write_RTCWEN();
    ALCFGRPTbits.ALRMEN = 0; 
    
    // Minutes + seconds
    ALCFGRPTbits.ALRMPTR = 0b00;
    ALRMVAL = (dec2bcd(t->min) << 8); 

    // Hours
    ALCFGRPTbits.ALRMPTR = 0b01;
    ALRMVAL = dec2bcd(t->hour);

    ALCFGRPTbits.AMASK = 0b0110; // Daily match (Match: Hour, Min, Sec)
    ALCFGRPTbits.ARPT  = 0xFF;   // Repeat 255 times
    ALCFGRPTbits.CHIME = 1;      // Enable rollover for infinite repeat
    
    RCFGCALbits.RTCWREN = 0;
}

void rtcc_set_alarm_enabled(bool enabled)
{
    __builtin_write_RTCWEN();
    ALCFGRPTbits.ALRMEN = enabled ? 1 : 0;
    RCFGCALbits.RTCWREN = 0;
}