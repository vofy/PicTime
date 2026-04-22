#include <xc.h>
#include <stdlib.h>
#include "rtcc.h"

const char* weekday_strings[7] = { "Ne", "Po", "Ut", "St", "Ct", "Pa", "So" };

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
}

void rtcc_get_time(struct tm *t)
{
    unsigned int val;

    // seconds + minutes
    RCFGCALbits.RTCPTR = 0b00;
    val = RTCVAL;
    t->tm_sec = bcd2dec(val & 0xFF);
    t->tm_min = bcd2dec((val >> 8) & 0xFF);

    // weekday + hours
    RCFGCALbits.RTCPTR = 0b01;
    val = RTCVAL;
    t->tm_hour = bcd2dec(val & 0xFF);
    t->tm_wday = bcd2dec((val >> 8) & 0xFF);

    // day + month
    RCFGCALbits.RTCPTR = 0b10;
    val = RTCVAL;
    t->tm_mday = bcd2dec(val & 0xFF);
    t->tm_mon  = bcd2dec((val >> 8) & 0xFF);

    // year (assume 2000?2099)
    RCFGCALbits.RTCPTR = 0b11;
    val = RTCVAL;
    t->tm_year = bcd2dec(val & 0xFF) + 100;

    t->tm_isdst = -1;
    
    mktime(t);
}

void rtcc_set_time(struct tm *t)
{
    unsigned int val;

    __builtin_write_RTCWEN();

    // seconds + minutes
    RCFGCALbits.RTCPTR = 0b00;
    val = (dec2bcd(t->tm_min) << 8) | dec2bcd(t->tm_sec);
    RTCVAL = val;

    // weekday + hours
    RCFGCALbits.RTCPTR = 0b01;
    val = (dec2bcd(t->tm_wday) << 8) | dec2bcd(t->tm_hour);
    RTCVAL = val;

    // day + month
    RCFGCALbits.RTCPTR = 0b10;
    val = (dec2bcd(t->tm_mon) << 8) | dec2bcd(t->tm_mday);
    RTCVAL = val;

    // year (two digits)
    RCFGCALbits.RTCPTR = 0b11;
    val = dec2bcd((t->tm_year + 1900) % 100);
    RTCVAL = val;

    RCFGCALbits.RTCWREN = 0;
}

void rtcc_set_alarm(const HrMin *t)
{
    __builtin_write_RTCWEN();
    ALCFGRPTbits.ALRMEN = 0; 
    
    // minutes + seconds
    ALCFGRPTbits.ALRMPTR = 0b00;
    ALRMVAL = (dec2bcd(t->min) << 8); 

    // hours
    ALCFGRPTbits.ALRMPTR = 0b01;
    ALRMVAL = dec2bcd(t->hour);

    ALCFGRPTbits.AMASK = 0b0010; // Daily match
    ALCFGRPTbits.CHIME = 1;
    RCFGCALbits.RTCWREN = 0;
}

void rtcc_set_alarm_enabled(bool enabled)
{
    __builtin_write_RTCWEN();
    ALCFGRPTbits.ALRMEN = enabled ? 1 : 0;
    RCFGCALbits.RTCWREN = 0;
}

const char *rtcc_weekday_str(struct tm *t)
{
    return weekday_strings[t->tm_wday];
}

const int rtcc_week_number(struct tm *t)
{
    struct tm tmp = *t;
    time_t ts = mktime(&tmp);
    struct tm *pt = localtime(&ts);

    char buf[3];
    strftime(buf, sizeof(buf), "%V", pt); // ISO week number

    return atoi(buf);
}