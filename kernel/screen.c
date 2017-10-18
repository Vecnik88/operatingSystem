/* Драйвера экрана */

#include "screen.h"

/*размер видеобуфера 80х25*/
u16_int *video_memory = (u16_int *)0xB8000;

/*строка, определяющая положение курсора*/
u8_int cursor_row = 0;

/*столбец определяющий положение курсора*/				
u8_int cursor_column = 0;

/*устанавливаем позицию курсора*/
static void set_cursor_position()
{
	u16_int cursor_position = cursor_column * 80 + cursor_row;

	out_byte(0x3D4, 14);                  // говорим VGA установить high byte
    out_byte(0x3D5, cursorLocation >> 8); // отправляем high byte курсора
    out_byte(0x3D4, 15);                  // говорим VGA установить low byte
    out_byte(0x3D5, cursorLocation);      // отправляем low byte курсора
}

/*скроллинг экрана*/
static void scroll_screen()
{
    u8_int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16_int blank = 0x20 /* space */ | (attributeByte << 8);

    if(cursor_column >= 25) {
        u32_int i;
        for (i = 0; i < 24*80; i++) {
            video_memory[i] = video_memory[i+80];
        }

        for (i = 24*80; i < 25*80; i++) {
            video_memory[i] = blank;
        }

        cursor_column = 24;
    }
}

/*выводим символ на экран*/
void put_screen(s8_int c)
{
    u8_int back_colour = 0;
    u8_int fore_colour = 15;

    u8int  attribute_byte = (back_colour << 4) | (fore_colour & 0x0F);

    u16_int attribute = attribute_byte << 8;
    u16_int *location;

    if (c == 0x08 && cursor_row) {
        cursor_row--;
    } else if (c == 0x09) {
        cursor_row = (cursor_row + 8) & ~(8 - 1);
    } else if (c == '\r') {
        cursor_row = 0;
    } else if (c == '\n') {
        cursor_row = 0;
        cursor_column++;
    } else if(c >= ' ') {
        location = video_memory + (cursor_column * 80 + cursor_row);
        *location = c | attribute;
        cursor_row++;
    }

    if (cursor_row >= 80) {
        cursor_row = 0;
        cursor_column++;
    }

    scroll_screen();
	set_cursor_position();
}

/*очищаем монитор*/
void clear_screen()
{
    u8_int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16_int blank = 0x20 /* space */ | (attributeByte << 8);

    u32_int i;
    for (i = 0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }

    cursor_row = 0;
    cursor_column = 0;
    set_cursor_position();
}

/*выводит строку на экран*/
void write_screen(s8_int *c)
{
    u32_int i = 0;
    while (c[i]) {
        put_screen(c[i++]);
    }
}

void write_screen_hex(u32_int n)
{

}

void write_screen_dec(u32_int n)
{
    
}