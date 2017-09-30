#include "../cpu/types.h"
#include "ports.h"
#include "../kernel/util.h"

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

/* команды для контроллера VGA */
#define REG_SCREEN_CTRL 		0x3d4
#define REG_SCREEN_DATA 		0x3d5

void clear_monitor(void);										/* очищает экран */
u32_int k_print(s8_int*);										/* выводит строку на экран */
void k_print_char(s8_int);										/* печатает символ на экране */
u32_int k_print_dec(u32_int);									/* печатает десятизначное число 8-значным на экране */
u32_int k_print_hex(u32_int);									/* печатает десятизначное число 16-значным на экране */

