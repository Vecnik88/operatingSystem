#include "../cpu/types.h"

u8_int inb(u16_int port);
u16_int inw(u16_int port);
void outb(u16_int port, u8_int value);
void outw(u16_int port, u16_int value);

