#include "../drivers/types.h"

#define HEX_VALUE 0
#define DEC_VALUE 1

u32_int strlen(s8_int* str);
void memcpy(s8_int* src, s8_int* dst, u32_int val);
void memset (s8_int* destination, s8_int c, u32_int n);
void transfer_value(u32_int value, s8_int* buf, s8_int type);	/* переводит число в строку в соответствии с запрашиваемым типом */