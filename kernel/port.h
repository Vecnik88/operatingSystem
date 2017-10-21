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
void memcpy(u8_int *dest, const u8_int *src, u32_int len);
void memset(u8_int *dest, u8_int val, u32_int len);
s32_int strcmp(s8_int *str1, s8_int *str2);
s32_int *strcpy(s32_int *dest, const s32_int *src);
s32_int *strcat(s32_int *dest, const s32_int *src);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, u32_int line);
extern void panic_assert(const char *file, u32_int line, const char *desc);

#endif	/* PORTS_H */
