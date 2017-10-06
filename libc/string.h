#ifndef STRINGS_H
#define STRINGS_H

#include "../cpu/types.h"

void reverse(u8_int* str);
s32_int strlen(u8_int* str);
void i_t_o_a(s32_int n, s8_int* str);
void backspace(s8_int* str);
void append(s8_int* str, s8_int n);
s32_int strcmp(s8_int* str1, s8_int* str2);

#endif