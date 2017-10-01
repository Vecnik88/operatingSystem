#include "types.h"

#define VIDEO_ADDRESS_VGA 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4				/* цвет и шрифт для ошибок */

/* порты ввода вывода VGA */
#define VGA_CTRL 0x3d4
#define VGA_DATA 0x3d5

void clear_screen();
void k_print_at(s8_int* str, s32_int col, s32_int row);
void k_print(s8_int* str);