// common.h -- Определения типов данных и некоторых глобальных функций.
// Из руководства по разработке ядра James Molloy

#ifndef COMMON_H
#define COMMON_H

// Несколько замечательных типов, обеспечивающих межплатформенную стандартизацию размеров.
// Это определения для 32-битной платформы X86.

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#endif