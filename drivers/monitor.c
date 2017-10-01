#include "monitor.h"
#include "ports.h"
#include "../kernel/util.h"

s32_int get_cursor_offset();
void set_cursor_offset(s32_int offset);
s32_int print_char(s8_int c, s32_int col, s32_int row, s8_int attr);
s32_int get_offset(s32_int col, s32_int row);
s32_int get_offset_row(s32_int offset);
s32_int get_offset_col(s32_int offset);

/* печатает строку в соответствующих местах */
void k_print_at(s8_int* str, s32_int col, s32_int row)
{
	s32_int offset;
	if (col >= 0 && row >= 0) {
		offset = get_offset(col, row);
	} else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	u32_int i = 0;
	while (str[i]) {
		offset = print_char(str[i++], col, row, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void k_print(s8_int* str)
{
	k_print_at(str, -1, -1);
}

s32_int print_char(s8_int c, s32_int col, s32_int row, s8_int attr)
{
	s8_int* video_memory = (s8_int*)VIDEO_ADDRESS_VGA;

	if (!attr)
		attr = WHITE_ON_BLACK;

	if (col >= MAX_COLS || row >= MAX_ROWS) {
		video_memory[2*(MAX_COLS)*(MAX_ROWS) - 2] = 'E';
		video_memory[2*(MAX_COLS)*(MAX_ROWS) - 1] = RED_ON_WHITE;

		return get_offset(col, row);
	}

	s32_int offset;
	if (col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else
		offset = get_cursor_offset();

	if (c == '\n') {
		row = get_offset_row(offset);
		offset = get_offset(0, row + 1);
	} else {
		video_memory[offset] = c;
		video_memory[offset+1] = attr;
		offset += 2;
	}

	/* прокрутка экрана */
	if (offset >= MAX_ROWS*MAX_COLS*2) {
		u32_int i;
		for (i = 0; i < MAX_ROWS; ++i)
			mem_cpy(get_offset(0, i) + VIDEO_ADDRESS_VGA,
					get_offset(0, i-1) + VIDEO_ADDRESS_VGA,
					MAX_COLS * 2);

		s8_int* l_line = get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS_VGA;

		for (i = 0; i < MAX_COLS*2; ++i)
			l_line[i] = 0;

		offset -= 2* MAX_COLS;
	}

	set_cursor_offset(offset);

	return offset;
}

s32_int get_cursor_offset()
{
	out_byte(VGA_CTRL, 14);
	s32_int offset = in_byte(VGA_DATA) << 8;
	out_byte(VGA_CTRL, 15);
	offset += in_byte(VGA_DATA);

	return offset*2;
}

void set_cursor_offset(s32_int offset)
{
	offset /= 2;
	out_byte(VGA_CTRL, 14);
	out_byte(VGA_DATA, (u8_int)(offset >> 8));
	out_byte(VGA_CTRL, 15);
	out_byte(VGA_DATA, (u8_int)(offset & 0xff));
}

void clear_screen()
{
	u32_int i;
	u32_int vga_video_size = MAX_COLS * MAX_ROWS;
	s8_int* video_memory = (s8_int*)VIDEO_ADDRESS_VGA;

	for (i = 0; i < vga_video_size; ++i) {
		video_memory[i*2] = ' ';
		video_memory[i*2 + 1] = WHITE_ON_BLACK;
	}

	set_cursor_offset(get_offset(0,0));
}

s32_int get_offset(s32_int col, s32_int row)
{
	return (2 * (row * MAX_COLS + col));
}

s32_int get_offset_row(s32_int offset)
{
	return (offset/(2*MAX_COLS));
}
s32_int get_offset_col(s32_int offset)
{
	return (offset-(get_offset_row(offset)*2*MAX_COLS))/2;
}