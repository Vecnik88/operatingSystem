#include "monitor.h"

static u8_int cursor_x = 0;
static u8_int cursor_y = 0;
static u16_int* video_memory = (u16_int*)0xB8000;

/* обновляем аппаратный курсор */
static void move_cursor()
{
	/* вычисляем то место на котором должен находиться курсор */
	u16_int cursor_position = cursor_y * 80 + cursor_x;
	
	outb(0x3D4, 14);					// сообщаем плате VGA что посылаем старший байт курсора 
	outb(0x3D5, cursor_position >> 8);	// отправляем старший байт курсора
	outb(0x3D4, 15);					// сообщаем что посылаем младший байт курсора
	outb(0x3D5, cursor_position);		// отправляем младший байт курсора
}

static void scroll()
{
	u8_int attribute_byte = (0 << 4) | (15 & 0x0F);
	u16_int blank = 0x20 | (attribute_byte << 8);

	if(cursor_y >= 25)
	{
		int i = 0;
		for(i = 0*80; i < 24*80; ++i)
			video_memory[i] = video_memory[i+80];
	
		for(i = 24*80; i < 25*80; ++i)
			video_memory[i] = blank;

		cursor_y = 24;
	}
}

void monitor_put(s8_int c)
{
	u8_int back_color = 0;		// black
	/* 	0:черный, 1:синий, 2:зеленый, 3:циан, 4:красный, 5:мажента, 
		6:коричневый, 7:светло серый, 8:темно серый, 9:светло синий, 10:светло зеленый, 
		11:светлый циан, 12:светло красный, 13:светлый мажента, 14: светло коричневый, 15: белый. 
	 */
	u8_int text_color = 12;		// blue

	u8_int attribute_byte = (back_color << 4) | (text_color & 0x0F);
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

void monitor_write(s8_int* c)
{
	int i = 0;
	while(c[i])
		monitor_put(c[i++]);
}

void monitor_write_hex(u32_int n)
{
	s8_int str_hex[20] = "0";
	s8_int* train;
	transfer_value(n, str_hex, DEC_VALUE);

		monitor_write("0x");
		u32_int i = strlen(str_hex);

	while(i)
		monitor_put(str_hex[--i]);
}

void monitor_write_dec(u32_int n)
{
	s8_int str_dec[20] = "0";
	transfer_value(n, str_dec, HEX_VALUE);

	u32_int i = strlen(str_dec);
	while(i)
		monitor_put(str_dec[--i]);

	monitor_write("d");
}

void transfer_value(u32_int value, s8_int* buf, s8_int type) {
	u32_int div = 0;
	div = type == HEX_VALUE ? 8 : 16;

	u16_int i = 0;
	u32_int num = 0;
	u16_int result = 0;

	while(value) {
		num = value;
		value /= div;
		result = num - value*div;

		switch(result) {
			case 0: buf[i++] = '0'; break;
			case 1: buf[i++] = '1'; break;
			case 2: buf[i++] = '2'; break;
			case 3: buf[i++] = '3'; break;
			case 4: buf[i++] = '4'; break;
			case 5: buf[i++] = '5'; break;
			case 6: buf[i++] = '6'; break;
			case 7: buf[i++] = '7'; break;
			case 8: buf[i++] = '8'; break;
			case 9: buf[i++] = '9'; break;
			case 10: buf[i++] = 'a'; break;
			case 11: buf[i++] = 'b'; break;
			case 12: buf[i++] = 'c'; break;
			case 13: buf[i++] = 'd'; break;
			case 14: buf[i++] = 'e'; break;
			case 15: buf[i++] = 'f'; break;
		}
	}
}

u32_int strlen(s8_int* str)
{
	u32_int count = 0;
	while(str[count++]) {}

		return count;
}

void memcpy(s8_int* src, s8_int* dst, u32_int val)
{
	while(val)
		dst[--val] = src[val];
}

void memset (s8_int* destination, s32_int c, u32_int n)
{
	while(n)
		destination[n--] = c;
}