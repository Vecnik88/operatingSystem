typedef unsigned int u32_int;
typedef int s32_int;
typedef unsigned short u16_int;
typedef short s16_int;
typedef unsigned char u8_int;
typedef char s8_int;

void outb(u16_int port, u8_int value);
u8_int inb(u16_int port);
u16_int inw(u16_int port);
