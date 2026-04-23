#ifndef INTERRUPT_H
#define	INTERRUPT_H

void timer_init(void);
void timer_clear_interrupt_flag(void);
bool timer_is_interrupt_active(void);

#endif
