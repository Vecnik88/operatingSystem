#include "string.h"

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

void append(s8_int* str, s8_int n)
{
	s32_int len = strlen(str);
	str[len] = n;
	str[len+1] = '\0';
}

void backspace(s8_int* str)
{
	s32_int len = strlen(str);
	str[len-1] = '\0';
}

s32_int strcmp(s8_int* str1, s8_int* str2)
{
	u32_int i;
	for (i = 0; str1[i] == str2[i]; ++i) {
		if (str1[i] == '\0')
			return 0;
	}

	return str1[i] - str2[i];
}