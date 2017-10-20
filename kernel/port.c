#include "port.h"

u8_int in_byte(u16_int port)
{
	u8_int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16_int in_word(u16_int port)
{
	u16_int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void out_byte(u16_int port, u8_int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void out_word(u16_int port, u16_int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void memcpy(u8_int *dest, const u8_int *src, u32_int len)
{
    // TODO: implement this yourself!
}

// Write len copies of val into dest.
void memset(u8_int *dest, u8_int val, u32_int len)
{
    // TODO: implement this yourself!
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
u32_int strcmp(s8_int *str1, s8_int *str2)
{
    // TODO: implement this yourself!
}

// Copy the NULL-terminated string src into dest, and
// return dest.
s8_int *strcpy(s8_int *dest, const s8_int *src)
{
    // TODO: implement this yourself!
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
s8_int *strcat(s8_int *dest, const s8_int *src)
{
    // TODO: implement this yourself!
}
