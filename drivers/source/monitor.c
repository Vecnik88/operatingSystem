#include "../include/monitor.h"

static u8_int cursor_x = 0;
static u8_int cursor_y = 0;
static u16_int* video_memory = (u16_int*)0xB8000;

static void move_cursor()
{
	u16_int cursor_position = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursor_position >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursor_position);
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

void monitor_put(char c)
{
	u8_int back_color = 0;		// black
	/* 	0:черный, 1:синий, 2:зеленый, 3:циан, 4:красный, 5:мажента, 
		6:коричневый, 7:светло серый, 8:темно серый, 9:светло синий, 10:светло зеленый, 
		11:светлый циан, 12:светло красный, 13:светлый мажента, 14: светло коричневый, 15: белый. 
	 */
	u8_int text_color = 1;		// blue

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

void monitor_clear()
{
	u8_int attribute_byte = (0 << 4) | (15 & 0x0F);
	u16_int blank = 0x20 | (attribute_byte << 8);

	int i = 0;
	for(i = 0; i < 80*25; ++i)
		video_memory[i] = blank;

	cursor_y = 0;
	cursor_x = 0;
	move_cursor();
}

void monitor_write(char* c)
{
	int i = 0;
	while(c[i])
		monitor_put(c[i++]);
}