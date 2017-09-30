#ifndef TYPES_H
#define TYPES_H

typedef unsigned int 	u32_int;
typedef int 			s32_int;
typedef unsigned short 	u16_int;
typedef short 			s16_int;
typedef unsigned char 	u8_int;
typedef char 			s8_int;

#define low_16(address) (u16_int)((address) & 0xffff)
#define high_16(address) (u16_int)(((address) >> 16) & 0xffff)

#endif