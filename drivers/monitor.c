#include "monitor.h"

static u8_int cursor_x = 0;
static u8_int cursor_y = 0;
static u8_int text_color = COLOR_WHITE;
static u8_int background_color = COLOR_BLACK;
static u16_int* video_memory = (u16_int*)0xB8000;

/* обновляем аппаратный курсор */
static void move_cursor()
{
	/* вычисляем то место на котором должен находиться курсор */
	u16_int cursor_position = cursor_y * 80 + cursor_x;

	outb(REG_SCREEN_CTRL, 14);						// сообщаем плате VGA что посылаем старший байт курсора 
	outb(REG_SCREEN_DATA, cursor_position >> 8);	// отправляем старший байт курсора
	outb(REG_SCREEN_CTRL, 15);						// сообщаем что посылаем младший байт курсора
	outb(REG_SCREEN_DATA, cursor_position);			// отправляем младший байт курсора
}

static void scroll()
{
	/* делаем символ пробела с атрибутами цвета, заданными по умолчанию */
	u8_int attribute_byte = (background_color << 4) | (text_color & 0x0F);
	u16_int blank = 0x20 | (attribute_byte << 8);

	if(cursor_y >= 25)
	{
		int i = 0;
		for(i = 0*80; i < 24*80; ++i)
			video_memory[i] = video_memory[i+80];
	
		for(i = 24*80; i < MONITOR_SIZE; ++i)
			video_memory[i] = blank;

		cursor_y = 24;
	}
}

void k_print_char(s8_int c)
{
	u8_int attribute_byte = (background_color << 4) | (text_color & 0x0F);
	u16_int attribute = attribute_byte << 8;
	u16_int * location;
	
	if(c == 0x08 && cursor_x)
	{
		--cursor_x;
	} else if(c == 0x09)
	{
		cursor_x = (cursor_x + 8) & ~(8-1);
	} else if(c == '\n')
	{
		cursor_x = 0;
		++cursor_y;
	} else if(c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		++cursor_x;
	}
	scroll();
	move_cursor();
}

void clear_monitor(void)
{
	u8_int attribute_byte = (0 << 4) | (15 & 0x0F);
	u16_int blank = 0x20 | (attribute_byte << 8);

	int i = 0;
	for(i = 0; i < MONITOR_SIZE; ++i)
		video_memory[i] = blank;

	cursor_y = 0;
	cursor_x = 0;
	move_cursor();
}

u32_int k_print(s8_int* c)
{
	u32_int i = 0;
	while(c[i])
		k_print_char(c[i++]);

	return i;
}

u32_int k_print_hex(u32_int n)
{
	s8_int str_hex[20] = "0";
	s8_int* train;
	transfer_value(n, str_hex, DEC_VALUE);

		k_print("0x");
		u32_int i = strlen(str_hex);

	while(i)
		k_print_char(str_hex[--i]);

	return strlen(str_hex);
}

u32_int k_print_dec(u32_int n)
{
	s8_int str_dec[20] = "0";
	transfer_value(n, str_dec, HEX_VALUE);

	u32_int i = strlen(str_dec);

	while(i)
		k_print_char(str_dec[--i]);

	k_print("d");

	return strlen(str_dec);
}