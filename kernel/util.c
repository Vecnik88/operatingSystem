#include "util.h"

void mem_cpy(s8_int* src, s8_int* dst, u32_int s_byte)
{
	u32_int i;
	for (i = 0; i < s_byte; ++i)
		dst[i] = src[i];
}

void i_t_o_a(s32_int n, s8_int* str)
{
	s32_int i = 0, sign = n;

	if (sign < 0)
		n = -n;

	do {
		str[i++] = n % 10 + '0';
	} while ((n/=10) > 0);

	if (sign < 0)
		str[i++] = '-';

	str[i] = '\0';
}