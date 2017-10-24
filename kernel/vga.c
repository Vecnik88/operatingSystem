#include "vga.h"	

#define LINES				25
#define LINES_SCREEN		24
#define COLUMNS				80
#define VGA_PORT_COMMAND	0x3d4
#define VGA_PORT_DATA		0x3d5
#define VGA_BUFFER_START 	0xb8000
#define VGA_BUFFER_END		0xc0000

enum vga_color {
	VGA_COLOR_BLACK			= 0,
	VGA_COLOR_BLUE 			= 1,
	VGA_COLOR_GREEN 		= 2,
	VGA_COLOR_CYAN 			= 3,
	VGA_COLOR_RED 			= 4,
	VGA_COLOR_MAGENTA 		= 5,
	VGA_COLOR_BROWN 		= 6,
	VGA_COLOR_LIGHT_GREY 	= 7,
	VGA_COLOR_DARK_GREY 	= 8,
	VGA_COLOR_LIGHT_BLUE 	= 9,
	VGA_COLOR_LIGHT_GREEN 	= 10,
	VGA_COLOR_LIGHT_CYAN 	= 11,
	VGA_COLOR_LIGHT_RED 	= 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN 	= 14,
	VGA_COLOR_WHITE 		= 15,
};

typedef uint32_t size_t;

static uint32_t cursor_col = 0;
static uint32_t cursor_line = 0;
static uint8_t text_color = VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4);
static short *video_memory = (short *)VGA_BUFFER_START;

/* API для удобства работы с цветом текста */
static inline uint8_t vga_entry_color(enum vga_color fore_color, 
									  enum vga_color background_color)
{
	return fore_color | background_color << 4;
}

static inline void vga_set_color_text(enum vga_color color_text)
{
	text_color = color_text | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_blue()
{
	text_color = VGA_COLOR_BLUE | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_green()
{
	text_color = VGA_COLOR_GREEN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_cyan()
{
	text_color = VGA_COLOR_CYAN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_red()
{
	text_color = VGA_COLOR_RED | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_magenta()
{
	text_color = VGA_COLOR_MAGENTA | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_brown()
{
	text_color = VGA_COLOR_BROWN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_grey()
{
	text_color = VGA_COLOR_LIGHT_GREY | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_dark_grey()
{
	text_color = VGA_COLOR_DARK_GREY | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_blue()
{
	text_color = VGA_COLOR_LIGHT_BLUE | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_green()
{
	text_color = VGA_COLOR_LIGHT_GREEN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_cyan()
{
	text_color = VGA_COLOR_LIGHT_CYAN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_red()
{
	text_color = VGA_COLOR_LIGHT_RED | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_magenta()
{
	text_color = VGA_COLOR_LIGHT_MAGENTA | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_light_brown()
{
	text_color = VGA_COLOR_LIGHT_BROWN | (VGA_COLOR_BLACK << 4);
}

static inline void vga_set_color_text_white()
{
	text_color = VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4);
}

static inline uint16_t get_blank_attr()
{
	uint8_t blank = text_color;
	return 0x20 | (blank << 8);
}

/* обновляет позицию курсора в соответствии с видеобуфером */
static void set_position_cursor()
{
	uint16_t position_cursor = cursor_line * COLUMNS + cursor_col;

	out_byte(VGA_PORT_COMMAND, 14);
	out_byte(VGA_PORT_DATA, (position_cursor >> 8));
	out_byte(VGA_PORT_COMMAND, 15);
	out_byte(VGA_PORT_DATA, position_cursor);
}

static void scroll()
{
    if(cursor_line >= LINES) {
        int i;
        for (i = 0; i < LINES_SCREEN * COLUMNS; i++)
            video_memory[i] = video_memory[i + COLUMNS];

        uint16_t blank = get_blank_attr();
        
        for (i = LINES_SCREEN * COLUMNS; i < LINES * COLUMNS; i++)
            video_memory[i] = blank;

        cursor_line = LINES_SCREEN;
    }
}

/* выводит символ на экран */
void monitor_put_char(char symbol)
{
    uint16_t *location; 

    if (symbol == 0x08 && cursor_col) {
        cursor_col--;
    } else if (symbol == 0x09) {
        cursor_col = (cursor_col + 8) & ~(8 - 1);
    } else if (symbol == '\r') {
        cursor_col = 0;
    } else if (symbol == '\n') {
        cursor_col = 0;
        cursor_line++;
    } else if(symbol >= ' ') {
        location = video_memory + (cursor_line * 80 + cursor_col);
        *location = symbol | text_color << 8;
        cursor_col++;
    }

    if (cursor_col >= 80) {
        cursor_col = 0;
        cursor_line++;
    }

    scroll();
    set_position_cursor();
}

/* очищает монитор */
void monitor_clear()
{
	uint16_t blank = get_blank_attr();

	int i;
	for (i = 0; i <= LINES * COLUMNS; ++i)
		video_memory[i] = blank;

	cursor_col = 0;
	cursor_line = 0;

	set_position_cursor();
}

/* выводит строку на экран */
void monitor_write(char* str)
{
	int i = 0;
	while (str[i])
		monitor_put_char(str[i++]);
}

/* происходит инициализация экрана */
void monitor_init()
{
	cursor_line = 0;
	cursor_col = 0;
	vga_set_color_text_white();
}

size_t strlen(const char* str)
{
	size_t i = 0;
	while (str[i])
		++i;

	return i;
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
			monitor_put_char(bytes[i]);
	return true;
}

//##############################################################################################################################
