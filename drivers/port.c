#include "port.h"

uint8_t in_byte(uint16_t port)
{
	uint8_t recv_byte;
	asm volatile ("in %%dx, %%al" : "=a" (recv_byte) : "d"(port));

	return recv_byte;
}

void out_byte(uint16_t port, uint8_t data)
{
	asm volatile ("out %%al, %%dx" : : "a"(data), "d"(port));
}

uint16_t in_word(uint16_t port)
{
	uint16_t recv_word;
	asm volatile ("in %%dx, %%ax" : "=a" (recv_word) : "d"(port));

	return recv_word;
}
void out_word(uint16_t port, uint16_t data)
{
	asm volatile ("out %%ax, %%dx" : : "a"(data), "d"(port));
}