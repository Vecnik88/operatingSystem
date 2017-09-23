#include "../include/common.h"

#define HEX_VALUE 0
#define DEC_VALUE 1

void monitor_put(char c);
void monitor_clear();
void monitor_write(char* c);
void monitor_write_hex(u32_int n);
void monitor_write_dec(u32_int n);
void transfer_value(u32_int value, char* buf, s8_int type);
u32_int strlen(s8_int* str);
/*void memset();
void memcpy();
void strcmp();*/