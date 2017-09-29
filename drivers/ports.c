#include "ports.h"

/* отправляем байт в порт */
void outb(u16_int port, u8_int value)
{
	__asm__ __volatile__ ("out %%ax, %%dx" : : "a" (value), "d" (port));
}

/* отправляем 2 байта в порт */
void outw(u16_int port, u16_int data) {
	__asm__ __volatile__("out %%al, %%dx" : : "a"(data), "d"(port));
}

/* получаем байт из порта */
u8_int inb(u16_int port)
{
	u8_int ret;
	__asm__ __volatile__("in %%dx, %%al" : "=a"(ret) : "d" (port));
	return ret;
}

/* получаем два байта из порта */
u16_int inw(u16_int port)
{
	u16_int ret;
	__asm__ __volatile__("in %%dx, %%ax" : "=a" (ret) : "d" (port));

	return ret;
}