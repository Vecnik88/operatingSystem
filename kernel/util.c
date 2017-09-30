#include "util.h"

u32_int strlen(s8_int* str)
{
	u32_int count = 0;
	while(str[count++]) {}

		return count;
}

void memcpy(s8_int* src, s8_int* dst, u32_int val)
{
	while(val)
		dst[--val] = src[val];
}

void memset(s8_int* destination, s8_int c, u32_int n)
{
	while(n)
		destination[n--] = c;
}

void int_to_asci(u32_int n, char* str)
{
	s32_int i = 0, sign = 0;
	if((sign = n) < 0)
		n = -n;
	
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while((n /= 10) > 0);

	if(sign < 0)
		str[i++] = '-';

	str[i] = '\0';
}

void transfer_value(u32_int value, s8_int* buf, s8_int type)
{
	u32_int div = 0;
	div = type == HEX_VALUE ? 8 : 16;

	u16_int i = 0;
	u32_int num = 0;
	u16_int result = 0;

	while(value) {
		num = value;
		value /= div;
		result = num - value*div;

		switch(result) {
			case 0: buf[i++] = '0'; break;
			case 1: buf[i++] = '1'; break;
			case 2: buf[i++] = '2'; break;
			case 3: buf[i++] = '3'; break;
			case 4: buf[i++] = '4'; break;
			case 5: buf[i++] = '5'; break;
			case 6: buf[i++] = '6'; break;
			case 7: buf[i++] = '7'; break;
			case 8: buf[i++] = '8'; break;
			case 9: buf[i++] = '9'; break;
			case 10: buf[i++] = 'a'; break;
			case 11: buf[i++] = 'b'; break;
			case 12: buf[i++] = 'c'; break;
			case 13: buf[i++] = 'd'; break;
			case 14: buf[i++] = 'e'; break;
			case 15: buf[i++] = 'f'; break;
		}
	}
}