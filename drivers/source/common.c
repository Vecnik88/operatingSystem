#include "common.h"

void outb(u16_int port, u8_int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16_int port)
{
	u8_int ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "dN" (port));
	return ret;
}

u16int inw(u16_int port)
{
	u16_int ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}