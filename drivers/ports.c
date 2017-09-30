#include "ports.h"

u8_int in_byte(u16_int port)
{
	u8_int recv_byte;
	__asm__ __volatile__ ("in %%dx, %%al" : "=a" (recv_byte) : "d"(port));

	return recv_byte;
}

void out_byte(u16_int port, u8_int data)
{
	__asm__ __volatile__ ("out %%al, %%dx" : : "a"(data), "d"(port));
}
u16_int in_word(u16_int port)
{
	u16_int recv_word;
	__asm__ __volatile__ ("in %%dx, %%ax" : "=a" (recv_word) : "d"(port));

	return recv_word;
}
void out_word(u16_int port, u16_int data)
{
	__asm__ __volatile__ ("out %%ax, %%dx" : : "a"(data), "d"(port));
}