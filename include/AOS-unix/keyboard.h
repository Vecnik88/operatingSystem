#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <AOS-unix/port.h>
#include <AOS-unix/isr.h>

#define SC_MAX 57
#define ENTER 0x1C
#define BACKSPACE 0x0E

/* для буфера, когда будет реализован планировщик */
static char key_buffer[256];

void init_keyboard();

#endif	/* KEYBOARD_H */