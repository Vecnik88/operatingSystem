#ifndef PORTS_H
#define PORTS_H

typedef unsigned int		u32_int;
typedef int 				s32_int;
typedef unsigned short		u16_int;
typedef short				s16_int;
typedef unsigned char		u8_int;
typedef char				s8_int;

u8_int in_byte(u16_int port);
u16_int in_word(u16_int port);
void out_byte(u16_int port, u8_int value);
void out_word(u16_int port, u16_int value);

#endif	/* PORTS_H */