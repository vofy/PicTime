#include <xc.h>
#include "adc.h"

void initAdc()
{
	AD1PCFGbits.PCFG4 = 0;  //Disable digital input on AN4	
	AD1PCFGbits.PCFG5 = 0;  //Disable digital input on AN5

	AD1CON1 = 0x00E0;		//Turn-on, auto-sample, manual mode
	AD1CON2 = 0;			//AVdd, AVss, int every conversion, MUXA only
	AD1CON3 = 0x1F05;		//31 Tad auto-sample, Tad = 5*Tcy
	AD1CSSL = 0;			//No scanned inputs
	AD1CON1bits.ADON = 1;
}


unsigned int sampleAdc()
{
	AD1CON1bits.SAMP = 1;   
	while(!AD1CON1bits.DONE);          
	return  ADC1BUF0;   
}


void setChannelAdc(unsigned char chan)
{
	if(chan >16)
		return;
	AD1CON1bits.ADON = 0;
	AD1CHS = chan;
	AD1CON1bits.ADON = 1;
}

