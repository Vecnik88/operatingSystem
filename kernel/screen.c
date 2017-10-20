#include "port.h"

u16_int *vga_buffer = (u16_int *) 0xb8000;

u8_int cursor_row = 0;					
u8_int cursor_col = 0;

static void set_cursor_position()
{
    u16_int cursor_position = cursor_col * 80 + cursor_row;

    out_byte(0x3D4, 14);
    out_byte(0x3D5, cursor_position >> 8);
    out_byte(0x3D4, 15);
    out_byte(0x3D5, cursor_position);
}

static void scroll()
{
    u8_int attribute_byte = (0 << 4) | (15 & 0x0F);
    u16_int blank = 0x20 | (attribute_byte << 8);

    if(cursor_col >= 25) {
        u32_int i;
        for (i = 0*80; i < 24*80; i++) {
            vga_buffer[i] = vga_buffer[i+80];
        }

        for (i = 24*80; i < 25*80; i++) {
            vga_buffer[i] = blank;
        }

        cursor_col = 24;
    }
}

void add_screen_char(s8_int c)
{
    u8_int background_color = 0;
    u8_int fore_color = 15;

    u8_int  attribute_byte = (background_color << 4) | (fore_color & 0x0F);

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
        cursor_col++;
    } else if(c >= ' ') {
        location = vga_buffer + (cursor_col*80 + cursor_row);
        *location = c | attribute;
        cursor_row++;
    }

    if (cursor_row >= 80) {
        cursor_row = 0;
        cursor_col++;
    }

    scroll();
    set_cursor_position();
}

void screen_clear()
{
    u8_int attribute_byte = (0 << 4) | (15 & 0x0F);
    u16_int blank = 0x20 | (attribute_byte << 8);

    u32_int i;
    for (i = 0; i < 80*25; i++) {
        vga_buffer[i] = blank;
    }

    cursor_row = 0;
    cursor_col = 0;

    set_cursor_position();
}

void screen_write(s8_int *c)
{
    u32_int i = 0;
    while (c[i])
    {
        add_screen_char(c[i++]);
    }
}

void screen_write_hex(u32_int n)
{
    s32_int tmp;

    screen_write("0x");

    s8_int no_zero = 1;

    u32_int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && no_zero != 0) {
            continue;
        }
    
        if (tmp >= 0xA) {
            no_zero = 0;
            add_screen_char (tmp-0xA+'a' );
        } else {
            no_zero = 0;
            add_screen_char( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA) {
        add_screen_char(tmp-0xA + 'a');
    } else {
        add_screen_char(tmp + '0');
    }
}

void screen_write_dec(u32_int n)
{
    if (n == 0) {
        add_screen_char('0');
        return;
    }

    s32_int acc = n;
    s8_int c[32];
    u32_int i = 0;
    while (acc > 0) {
        c[i] = '0' + acc % 10;
        acc /= 10;
        i++;
    }
    c[i] = '0';

    s8_int c2[32];
    c2[i--] = '0';
    u32_int j = 0;

    while(i >= 0) {
        c2[i--] = c[j++];
    }

    screen_write(c2);
}
