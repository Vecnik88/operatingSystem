#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

size_t strlen(const char *str);
void *memcpy(void *dst, const void *src, size_t size);
void *memset(void *dst, int fill, size_t size);
void itoa(int n, char s[]);
int strcmp(char *str1, char *str2);

#endif /*__STRING_H__*/