//*****************************************************************************
// zdroj:		rtcc.c
// MCU:			PIC24FJ128GA010
//*****************************************************************************

#include <p24fxxxx.h>
#include <time.h>
#include "rtcc.h"

// inicializace
//
void initRtcc()
{
	// nastaveni druheho oscilatoru
	CLKDIV = 0;
  	__builtin_write_OSCCONL(0x02); 
  	while(!OSCCONbits.SOSCEN);
    // nastaveni rtcc modulu
	__builtin_write_RTCWEN();
  	RCFGCALbits.RTCEN = 1;
  	RCFGCALbits.RTCWREN = 0;
}

// Zapis casu do RTCC
// pointer ukazuje na pole typu unsigned char [6]
// |  0   |   1  ||  2   |  3   ||  4   |  5   |
// |hodDes|hodJed||minDes|minJed||secDes|secJed|
//
void writeTimeRtcc(unsigned char* time)
{
	unsigned int minsec = 0;
	unsigned int hod = 0;
	unsigned int pom;
	unsigned char a;
	unsigned int *ptime;
	
	for(a=0; a<6; a++)
	{
		*time &= 0x0F;	
			
		if(a<2)
			ptime = &hod;
		else
			ptime = &minsec;
		//
		*ptime <<=4;			
		*ptime |= *time++;
	}
	// zapis do registru RCFGCAL
	__builtin_write_RTCWEN();
	// min/sec
	RCFGCALbits.RTCPTR = 0b00;
	RTCVAL = minsec;
	// weekday/hod
	RCFGCALbits.RTCPTR = 0b01;
	pom = RTCVAL;
	pom &= 0xFF00;
	RCFGCALbits.RTCPTR = 0b01;
	pom |= hod;		
	RTCVAL = pom;
	// reset
	RCFGCALbits.RTCWREN = 0;
}
// Zapis datumu do RTCC
// pointer ukazuje na pole typu unsigned char [9]
// |  0   |   1  ||  2   |  3   ||  4   |  5   |  6   |  7   ||    8   |
// |dnyDes|dnyJed||mesDes|mesJed||rokTis|rokSto|rokDes|rokJed||dnyTyden|
//
void writeDateRtcc(unsigned char* date)
{
	unsigned int den = 0;
	unsigned int mes = 0;
	unsigned int rok = 0;
	unsigned int wd = 0;
	unsigned int pom;
	unsigned char a;
	unsigned int *pdate;

	for(a=0; a<8; a++)
	{
		*date &= 0x0F;		
		if(a<2)
			pdate =&den;
		else if(a<4)
			pdate =&mes;
		else 
			pdate =&rok;
		//
		*pdate <<=4;
		*pdate |= *date++;
	}
	*date &= 0x0F;	
	wd = *date;
	// zapis do registru RCFGCAL
	__builtin_write_RTCWEN();
	// weekday
	RCFGCALbits.RTCPTR = 0b01;
	wd <<= 8;	
	pom = RTCVAL;
	pom &= 0x00FF;
	RCFGCALbits.RTCPTR = 0b01;
	pom |= wd;
	RTCVAL = pom;
	// month/day	
	RCFGCALbits.RTCPTR = 0b10;
	mes <<= 8;
	mes |= den;	
	RTCVAL = mes;
	// year
	RCFGCALbits.RTCPTR = 0b11;
	rok &= 0x00FF;	
	RTCVAL = rok;
	// reset
	RCFGCALbits.RTCWREN = 0;
}

// Cteni casu z RTCC
// pointer ukazuje na pole typu unsigned char [6]
// |  0   |   1  ||  2   |  3   ||  4   |  5   |
// |hodDes|hodJed||minDes|minJed||secDes|secJed|
//
void readTimeRtcc(unsigned char* time)
{
	unsigned int pom;
	unsigned char a;
	time += 5;

	// min/sec
	RCFGCALbits.RTCPTR = 0b00;
	pom = RTCVAL;
	for(a=0; a<4; a++)
	{
		*time-- = (unsigned char)(pom & 0x000F);
		pom >>= 4;	
	}
	// x/hod
	RCFGCALbits.RTCPTR = 0b01;
	pom = RTCVAL;
	*time-- = (unsigned char)(pom & 0x000F);
	pom >>= 4;
	*time = (unsigned char)(pom & 0x000F);
}

static int bcd2dec(unsigned int bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void readTimeTimehRtcc(struct tm *t)
{
    // Read seconds and minutes
    RCFGCALbits.RTCPTR = 0b00;

    int sec_bcd = RTCVAL & 0x00FF;
    int min_bcd = (RTCVAL >> 8) & 0x00FF;

    t->tm_sec = bcd2dec(sec_bcd);
    t->tm_min = bcd2dec(min_bcd);

    // Read hours
    RCFGCALbits.RTCPTR = 0b01;

    int hour_bcd = RTCVAL & 0x00FF;
    t->tm_hour = bcd2dec(hour_bcd);
}


// Cteni datumu z RTCC
// pointer ukazuje na pole typu unsigned char [9]
// |  0   |   1  ||  2   |  3   ||  4   |  5   |  6   |  7   ||    8   |
// |dnyDes|dnyJed||mesDes|mesJed||rokTis|rokSto|rokDes|rokJed||dnyTyden|
//
void readDateRtcc(unsigned char* date)
{
	unsigned int pom;
	// wd/x
	RCFGCALbits.RTCPTR = 0b01;
	pom = RTCVAL;
	pom >>= 8;
	date[8] =(unsigned char)pom;
	// mes/dny
	RCFGCALbits.RTCPTR = 0b10;
	pom = RTCVAL;
	date[1] =(unsigned char)(pom & 0x000F);
	pom >>= 4;
	date[0] =(unsigned char)(pom & 0x000F);
	pom >>= 4;
	date[3] =(unsigned char)(pom & 0x000F);
	pom >>= 4;
	date[2] =(unsigned char)(pom & 0x000F);
	pom >>= 4;
	// x/rok
	RCFGCALbits.RTCPTR = 0b11;
	pom = RTCVAL;
	date[7] =(unsigned char)(pom & 0x000F);
	pom >>= 4;
	date[6] =(unsigned char)(pom & 0x000F);		
	date[5] = 0;
	date[4] = 2;
}
// cteni znaku casu z RTCC
// pointer ukazuje na pole typu char [8]
// HH:MM:SS
void readTimeCharRtcc(char* time)
{
    unsigned char buf[6];
    readTimeRtcc(buf);
    time[0] = (char)(buf[0]+'0');
    time[1] = (char)(buf[1]+'0');
    time[2] = ':';
    time[3] = (char)(buf[2]+'0');
    time[4] = (char)(buf[3]+'0');
    time[5] = ':';
    time[6] = (char)(buf[4]+'0');
    time[7] = (char)(buf[5]+'0');
    time[8] = 0;
}
//
void readDateCharRtcc(char* date)
{
    unsigned char buf[9];
    readDateRtcc(buf);
    date[0] = (char)(buf[0]+'0');
    date[1] = (char)(buf[1]+'0');
    date[2] = '.';
    date[3] = (char)(buf[2]+'0');
    date[4] = (char)(buf[3]+'0');
    date[5] = '.';
    date[6] = (char)(buf[4]+'0');
    date[7] = (char)(buf[5]+'0');
    date[8] = (char)(buf[6]+'0');
    date[9] = (char)(buf[7]+'0');
    date[10] = ' ';
    switch(buf[8])
    {
        case 0: date[11]='n'; date[12]='e'; date[13]='d';
            break;
        case 1: date[11]='p'; date[12]='o'; date[13]='n';
            break;
        case 2: date[11]='u'; date[12]='t'; date[13]='e';
            break;
        case 3: date[11]='s'; date[12]='t'; date[13]='r';
            break;
        case 4: date[11]='c'; date[12]='t'; date[13]='v';
            break;
        case 5: date[11]='p'; date[12]='a'; date[13]='t';
            break;
        case 6: date[11]='s'; date[12]='o'; date[13]='b';
            break;
    } 
    date[14] = 0;
}