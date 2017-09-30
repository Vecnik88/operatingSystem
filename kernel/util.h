#include "../cpu/types.h"

#define HEX_VALUE 0
#define DEC_VALUE 1

u32_int strlen(s8_int* );
void memcpy(s8_int* , s8_int* , u32_int);
void memset (s8_int* , s8_int, u32_int);
void transfer_value(u32_int, s8_int* , s8_int);	/* переводит число в строку в соответствии с запрашиваемым типом */