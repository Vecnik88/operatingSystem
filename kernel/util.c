#include "util.h"

void mem_cpy(s8_int* src, s8_int* dst, u32_int s_byte)
{
	u32_int i;
	for (i = 0; i < s_byte; ++i)
		dst[i] = src[i];
}

void mem_set(s8_int* dest, s8_int c, u32_int len)
{
	while (len)
		dest[--len] = c;
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

	reverse(str);
}

void reverse(u8_int* str)
{
	s32_int c, i, j;
	for (i = 0, j = strlen(str)-1; i < j; ++i, --j) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

s32_int strlen(u8_int* str)
{
	s32_int count = 0;
	while (str[count])
		++count;

	return count;
}