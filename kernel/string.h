#ifndef STRING_H
#define STRING_H

#include "types.h"

void memcpy(u8_int *dest, const u8_int *src, u32_int len);
void memset(u8_int *dest, u8_int val, u32_int len);
u32_int strcmp(s8_int *str1, s8_int *str2);
s8_int *strcpy(s8_int *dest, const s8_int *src);
s8_int *strcat(s8_int *dest, const s8_int *src);

#endif