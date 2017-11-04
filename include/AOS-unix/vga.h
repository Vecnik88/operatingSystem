#ifndef VGA_H
#define VGA_H

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

void monitor_init();
void monitor_write(char* str);
void monitor_clear();
void monitor_put_char(char symbol);
void monitor_backspace();

#endif	/* VGA_H */