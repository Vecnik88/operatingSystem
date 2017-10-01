#include "mem.h"

void mem_cpy(u8_int* src, u8_int* dst, u32_int count)
{
	u32_int i;
	for (i = 0; i < count; ++i)
		dst[i] = src[i];
}

void mem_set(u8_int* dest, u8_int value, u32_int len)
{
	while(len)
		dest[len--] = value;
}