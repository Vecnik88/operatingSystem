#ifndef SCREEN_H
#define SCREEN_H

#include "port.h"

void screen_clear();
void screen_write();
void add_screen_char(s8_int c);
void screen_write_hex(u32_int n);
void screen_write_dec(u32_int n);

#endif