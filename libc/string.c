#include <AOS-unix/string.h>

size_t strlen(const char *str)
{
	const char *begin = str;

	while (*str++);
    
	return str - begin - 1;
}

int strcmp(char *str1, char *str2)
{
    if (!str1 || !str2)
        return -1;
    
    int i;
    for (i = 0; i < strlen(str1); ++i)
        if (str1[i] == str2[i])
            continue;
        else return -1;

    return 0;
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

void reverse(char s[])
{
    int i, j;
    char c;
 
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
 
    if ((sign = n) < 0)				/* записываем знак */
        n = -n;						/* делаем n положительным числом */
    
    i = 0;
    do {							/* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';		/* берем следующую цифру */
    } while ((n /= 10) > 0);		/* удаляем */
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';

    reverse(s);
 }