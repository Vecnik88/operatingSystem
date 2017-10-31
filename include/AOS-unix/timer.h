#ifndef TIMER_H
#define TIMER_H

#include <AOS-unix/printk.h>
#include <AOS-unix/isr.h>
#include <AOS-unix/port.h>

void init_timer(uint32_t frequency);

#endif	/* TIMER_H */