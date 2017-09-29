//#include "common.h"

#define HEX_VALUE 0
#define DEC_VALUE 1

void monitor_put(s8_int c);
void monitor_clear();
void monitor_write(s8_int* c);
void monitor_write_hex(u32_int n);
void monitor_write_dec(u32_int n);
void transfer_value(u32_int value, s8_int* buf, s8_int type);
u32_int strlen(s8_int* str);
void memcpy(s8_int* src, s8_int* dst, u32_int val);
void memset (s8_int* destination, s32_int c, u32_int n);
/*void memset();
void memcpy();
void strcmp();*/