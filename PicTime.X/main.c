#include <p24fxxxx.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"
#include "adc.h"
#include "display.h"

_CONFIG1 (0x3F7F)	// Watchdog off, JTAG off, Code protection off
_CONFIG2 (0xFABD)	// primary osc on, XT without PLL (crystal)

#define LED         LATAbits.LATA0
#define TRIS_LED	TRISAbits.TRISA0

unsigned char sec, min, hr, pot;
char charBuffer[17]; 
char adcBuffer[17]; 
unsigned int resultAd;
unsigned int temp;

// interrupt TMR2
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt()
{
  	IFS0bits.T2IF = 1;
}

// set TMR2 for 8MHz
void initTimer2()
{
	T2CON = 0x0030;			// fosc/2=> 0.25us*256=64us 
 	PR2 = 15625;          	// 64us*15625 =1s
 	T2CONbits.TON = 1;		// Timer1 on
 	IFS0bits.T2IF = 0;		// interrupt flag
 	IEC0bits.T2IE = 0;		// interrupt on
}

// main
void main()
{
  	initTimer2();
  	initLcd();  
    initAdc();
	TRISA &= 0b1111111100000000;	//0xFF00
  	TRIS_LED = 0;
    
    int curr_time = 0;
    
    bool mode = true;

	while(1)
    {
        if(IFS0bits.T2IF == 1)
        {
            curr_time = curr_time + 1 ? curr_time < 86400 : 0; 
            displayUpdateTime(curr_time);

            IFS0bits.T2IF = 0;
            
            if(sec%5 == 0)
            {
                mode = !mode;
            }
            
            if (!mode)
            {
                setChannelAdc(4);
                temp = (((3.222*sampleAdc())-500)/10);
                sprintf(adcBuffer, "temp  %d", temp);
            }
        }
            
        if(mode)
        {
            setChannelAdc(5);
            resultAd = sampleAdc();
            resultAd >>= 2;
            LATA = resultAd;

            sprintf(adcBuffer, "pot   %d", resultAd);
        }

        setAddr2Lcd(0);
        writeLineLcd(adcBuffer);
    }
}