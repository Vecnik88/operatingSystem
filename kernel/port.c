#include "port.h"

u8_int in_byte(u16_int port)
{
	u8_int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16_int in_word(u16_int port)
{
	u16_int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void out_byte(u16_int port, u8_int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void out_word(u16_int port, u16_int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void memcpy(u8_int *dest, const u8_int *src, u32_int len)
{
    const u8_int *sp = (const u8_int *)src;
    u8_int *dp = (u8_int *)dest;

    for (; len != 0; len--) 
        *dp++ = *sp++;
}

void memset(u8_int *dest, u8_int val, u32_int len)
{
    u8_int *temp = (u8_int *)dest;
    for ( ; len != 0; len--) 
        *temp++ = val;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
s32_int strcmp(s8_int *str1, s8_int *str2)
{
      s32_int i = 0;
      s32_int failed = 0;
      while (str1[i] != '\0' && str2[i] != '\0') {
          if (str1[i] != str2[i]) {
              failed = 1;
              break;
          }
          i++;
      }

      if ((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
          failed = 1;
  
      return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
s32_int *strcpy(s32_int *dest, const s32_int *src)
{
    do {
      *dest++ = *src++;
    } while (*src != 0);
}

s32_int *strcat(s32_int *dest, const s32_int *src)
{
    while (*dest != 0) {
        *dest = *dest++;
    }

    do {
        *dest++ = *src++;
    } while (*src != 0);

    return dest;
}

extern void panic(const char *message, const char *file, u32_int line)
{
    asm volatile("cli");

    screen_write("PANIC(");
    screen_write(message);
    screen_write(") at ");
    screen_write(file);
    screen_write(":");
    screen_write(line);
    screen_write("\n");

    for(;;);
}

extern void panic_assert(const char *file, u32_int line, const char *desc)
{
    asm volatile("cli");

    screen_write("ASSERTION-FAILED(");
    screen_write(desc);
    screen_write(") at ");
    screen_write(file);
    screen_write(":");
    screen_write_dec(line);
    screen_write("\n");

    for(;;);
}
