#include <xc.h>
#include "buttons.h" 

#define S3  PORTDbits.RD6
#define S6  PORTDbits.RD7
#define S5  PORTAbits.RA7
#define S4  PORTDbits.RD13

Key read_key()
{
    if (!S3) { while(!S3); return KEY_ENTER; }
    if (!S6) { while(!S6); return KEY_ESC;   }
    if (!S5) { while(!S5); return KEY_PREV;  }
    if (!S4) { while(!S4); return KEY_NEXT;  }
    
    return KEY_NONE;
}