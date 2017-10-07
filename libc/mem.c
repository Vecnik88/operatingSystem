#include "mem.h"

void mem_cpy(s8_int* src, s8_int* dst, u32_int count)
{
	u32_int i;
	for (i = 0; i < count; ++i)
		*(dst + i) = *(src + i);
}

void mem_set(s8_int* dest, u8_int value, u32_int len)
{
	s8_int* temp = (s8_int*)dest;
	for ( ; len != 0; --len)
		*temp++ = value;
}