#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum {
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
} Button;

#define BUTTON_REPEAT_INITIAL 600  // Delay before first repeat (ms)
#define BUTTON_REPEAT_RATE    150  // Delay between subsequent repeats (ms)

#define S3 PORTDbits.RD6
#define S6 PORTDbits.RD7
#define S5 PORTAbits.RA7
#define S4 PORTDbits.RD13

void buttons_init(void);
void buttons_tick(void);
void buttons_check_state(void);

#endif