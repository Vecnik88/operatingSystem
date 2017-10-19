#include "port.h"

void out_byte(u16_int port, u8_int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8_int in_byte(u16_int port)
{
    u8_int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16_int in_word(u16_int port)
{
    u16_int ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}