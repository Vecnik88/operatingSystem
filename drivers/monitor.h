#include "ports.h"

#define MONITOR_SIZE 		(80*25)

/* цвета экрана */
#define COLOR_BLACK 			0
#define COLOR_BLUE 				1
#define COLOR_GREEN 			2
#define COLOR_CYAN 				3
#define COLOR_RED 				4
#define COLOR_MAZHENTA 			5
#define COLOR_BROWN 			6
#define COLOR_LIGHT_GRAY		7
#define COLOR_DARK_GRAY			8
#define COLOR_LIGHT_BLUE		9
#define COLOR_LIGHT_GREEN		10
#define COLOR_LIGHT_CYAN		11
#define COLOR_LIGHT_RED			12
#define COLOR_LIGHT_MASHENTE	13
#define COLOR_LIGHT_BROWN		14
#define COLOR_WHITE				15

#define HEX_VALUE 0
#define DEC_VALUE 1

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_monitor(void);					/* очищает экран */
u32_int k_print(s8_int*);					/* выводит строку на экран */
void k_print_char(s8_int);
u32_int k_print_dec(u32_int);
u32_int k_print_hex(u32_int);
//void monitor_put(s8_int c);
//void monitor_clear();
//void monitor_write(s8_int* c);
//void monitor_write_hex(u32_int n);
//void monitor_write_dec(u32_int n);
//void transfer_value(u32_int value, s8_int* buf, s8_int type);
//u32_int strlen(s8_int* str);
//void memcpy(s8_int* src, s8_int* dst, u32_int val);
//void memset (s8_int* destination, s32_int c, u32_int n);
/*void memset();
void memcpy();
void strcmp();*/