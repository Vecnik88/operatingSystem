#include <AOS-unix/vga.h>	

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

static uint32_t cursor_col = 0;
static uint32_t cursor_line = 0;
static uint8_t text_color = VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4);
static short *video_memory = (short *)VGA_BUFFER_START;



static void set_position_cursor()
{
	uint16_t position_cursor = cursor_col * COLUMNS + cursor_line;

	out_byte(VGA_PORT_COMMAND, 14);
	out_byte(VGA_PORT_DATA, (position_cursor << 8));
	out_byte(VGA_PORT_COMMAND, 15);
	out_byte(VGA_PORT_DATA, position_cursor);
}

static scroll()
{
	uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    if(cursor_line >= LINES) {
        int i;
        for (i = 0; i < LINES_SCREEN * COLUMNS; i++)
            video_memory[i] = video_memory[i + COLUMNS];

        for (i = LINES_SCREEN * COLUMNS; i < LINES * COLUMNS; i++)
            video_memory[i] = blank;

        cursor_line = LINES_SCREEN;
    }
}

/* API для удобства работы с цветом текста */
static inline uint8_t vga_entry_color(enum vga_color fore_color, enum vga_color background_color)
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
	return 0x20 | (text_color << 8);
}