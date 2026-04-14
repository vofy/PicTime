#include <xc.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

static time_t rtcc_stopwatch_start = 0;
static time_t rtcc_stopwatch_elapsed = 0;
static bool rtcc_stopwatch_running = false;

static int bcd2dec(unsigned int bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static int dec2bcd(int dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

void rtcc_stopwatch_run()
{
    if (rtcc_stopwatch_running)
        return;

    struct tm t;
    rtcc_get_time(&t);

    rtcc_stopwatch_start = mktime(&t);
    rtcc_stopwatch_running = true;
}

void rtcc_stopwatch_stop()
{
    if (!rtcc_stopwatch_running)
        return;

    struct tm t;
    rtcc_get_time(&t);

    time_t now = mktime(&t);
    rtcc_stopwatch_elapsed += now - rtcc_stopwatch_start;

    rtcc_stopwatch_start = 0;
    rtcc_stopwatch_running = false;
}

void rtcc_stopwatch_reset()
{
    rtcc_stopwatch_elapsed = 0;
    rtcc_stopwatch_start = 0;
    rtcc_stopwatch_running = false;
}

time_t rtcc_stopwatch_time()
{
    if (!rtcc_stopwatch_running)
        return rtcc_stopwatch_elapsed;

    struct tm t;
    rtcc_get_time(&t);

    time_t now = mktime(&t);
    return rtcc_stopwatch_elapsed + (now - rtcc_stopwatch_start);
}

bool rtcc_stopwatch_is_running()
{
    return rtcc_stopwatch_running;
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

const char *rtcc_weekday_str(struct tm *t)
{
    static const char *days[] = { "Ne", "Po", "Ut", "St", "Ct", "Pa", "So" };

    return days[t->tm_wday];
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