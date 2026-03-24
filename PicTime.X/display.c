#include "lcd.h"

void displayUpdateTime(int curr_time)
{
    char displayBuffer[17];
    
    int hrs = curr_time / 3600;
    int mins = hrs / 60;
    
    sprintf(displayBuffer, "%d:%d", hrs, mins);
    
    setAddr1Lcd(0);
    writeLineLcd(displayBuffer);
}