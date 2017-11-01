#include <AOS-unix/string.h>

size_t strlen(const char *str)
{
	const char *begin = str;

	while (*str++);
	return str - begin - 1;
}

void *memcpy(void *dst, const void *src, size_t size)
{
	char *to = dst;
	const char *from = src;

	while (size--)
		*to++ = *from++;
	return dst;
}

void *memset(void *dst, int fill, size_t size)
{
	char *to = dst;

	while (size--)
		*to++ = fill;
	return dst;
}

void reverse(char *s)
{
    int i, j;
    char c;
 
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char *s)
{
    int i, sign;
 
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
     if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    
    reverse(s);
}