#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum {
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
} Button;

void buttons_tick(void);
void buttons_check_state(void);

#endif