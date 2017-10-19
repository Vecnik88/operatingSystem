#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "port.h"

void put_screen(s8_int c);
void clear_screen();
void write_screen(s8_int *c);
void write_screen_hex(u32_int n);
void write_screen_dec(u32_int n);

#endif // SCREEN_H