#include "string.h"

void memcpy(u8_int *dest, const u8_int *src, u32_int len)
{
    const u8_int *sp = (const u8_int *)src;
    u8_int *dp = (u8_int *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

void memset(u8_int *dest, u8_int val, u32_int len)
{
    u8_int *temp = (u8_int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

u32_int strcmp(s8_int *str1, s8_int *str2)
{
      u32_int i = 0;
      u32_int failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0') {
          if(str1[i] != str2[i]) {
              failed = 1;
              break;
          }
          i++;
      }
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;
  
      return failed;
}


s8_int *strcpy(s8_int *dest, const s8_int *src)
{
    do {
      *dest++ = *src++;
    } while (*src != 0);
}

s8_int *strcat(s8_int *dest, const s8_int *src)
{
    while (*dest != 0) {
        *dest = *dest++;
    }

    do {
        *dest++ = *src++;
    } while (*src != 0);
    
    return dest;
}