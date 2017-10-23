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

struct print_ctx {
	int (*out)(struct print_ctx *ctx, const char *buf, int size);
	int written;
};

static int print(struct print_ctx *ctx, const char *buf, int size)
{
	const int rc = ctx->out(ctx, buf, size);

	if (rc < 0)
		return rc;

	ctx->written += size;
	return 0;
}

enum format_type {
	FMT_INVALID,
	FMT_NONE,
	FMT_STR,
	FMT_CHAR,
	FMT_INT,
	FMT_PERCENT,
};

enum fromat_spec {
	FMT_SSHORT = (1 << 8),
	FMT_SHORT = (1 << 9),
	FMT_LONG = (1 << 10),
	FMT_LLONG = (1 << 11),
	FMT_UNSIGNED = (1 << 12),
	FMT_HEX = (1 << 13),
	FMT_OCT = (1 << 14)
};

static int decode_format(const char **fmt_ptr)
{
	const char *fmt = *fmt_ptr;
	int type = FMT_INVALID;
	int spec = 0;

	while (*fmt) {
		if (*fmt == '%' && type != FMT_INVALID)
			break;

		char c = *fmt++;

		if (c != '%') {
			type = FMT_NONE;
			continue;
		}

		switch (*fmt) {
		case '-': case '+': case ' ': case '#': case '0':
			++fmt;
			break;
		}

		while (*fmt && isdigit(*fmt))
			++fmt;

		if (*fmt == '.') {
			++fmt;
			while (*fmt && isdigit(*fmt))
				++fmt;
		}

		if (*fmt == 'l') {
			++fmt;
			if (*fmt == 'l') {
				spec = FMT_LLONG;
				++fmt;
			} else {
				spec = FMT_LONG;
			}
		} else if (*fmt == 'h') {
			++fmt;
			if (*fmt == 'h') {
				spec = FMT_SSHORT;
				++fmt;
			} else {
				spec = FMT_SHORT;
			}
		}

		switch ((c = *fmt++)) {
		case 'p':
			spec |= FMT_LONG;
		case 'x': case 'X': case 'o':
			spec |= c == 'o' ? FMT_OCT : FMT_HEX;
		case 'u':
			spec |= FMT_UNSIGNED;
		case 'd': case 'i':
			type = FMT_INT;
			break;
		case 's':
			type = FMT_STR;
			break;
		case 'c':
			type = FMT_CHAR;
			break;
		case '%':
			type = FMT_PERCENT;
			break;
		}
		break;
	}
	*fmt_ptr = fmt;

	return type | spec;
}

static int print_number(struct print_ctx *ctx, va_list args, int type)
{
	const int base = (type & FMT_HEX) ? 16 : ((type & FMT_OCT) ? 8 : 10);
	char buf[64];

	if (type & FMT_UNSIGNED) {
		unsigned long long value;

		if (type & FMT_LONG)
			value = va_arg(args, unsigned long);
		else if (type & FMT_LLONG)
			value = va_arg(args, unsigned long long);
		else
			value = va_arg(args, unsigned);
		ulltoa(value, buf, base);
	} else {
		long long value;

		if (type & FMT_LONG)
			value = va_arg(args, long);
		else if (type & FMT_LLONG)
			value = va_arg(args, long long);
		else
			value = va_arg(args, int);
		lltoa(value, buf, base);
	}

	return print(ctx, buf, strlen(buf));
}

int __vprintf(struct print_ctx *ctx, const char *fmt, va_list args)
{
	int rc = 0;

	ctx->written = 0;

	while (rc >= 0 && *fmt) {
		const char *start = fmt;
		const int type = decode_format(&fmt);

		switch (type & 0xff) {
		case FMT_STR: {
			const char *str = va_arg(args, const char *);

			rc = print(ctx, str, strlen(str));
			break;
		}
		case FMT_CHAR: {
			const char c = va_arg(args, int);

			rc = print(ctx, &c, 1);
			break;
		}
		case FMT_INT:
			rc = print_number(ctx, args, type);
			break;
		case FMT_NONE:
			rc = print(ctx, start, fmt - start);
			break;
		case FMT_PERCENT:
			rc = print(ctx, "%", 1);
			break;
		default:
			rc = -1;
			break;
		}
	}

	return rc < 0 ? rc : ctx->written;
}

static int vga_out(struct print_ctx *ctx, const char *buf, int size)
{
	(void) ctx;

	vga_write(buf, (size_t)size);

	return 0;
}

int vprintf(const char *fmt, va_list args)
{
	struct print_ctx ctx = {
		.out = &vga_out,
		.written = 0
	};

	return __vprintf(&ctx, fmt, args);
}

struct print_str_ctx {
	struct print_ctx ctx;
	char *buf;
	int size;
};

static int str_out(struct print_ctx *ctx, const char *buf, int size)
{
	struct print_str_ctx *sctx = (struct print_str_ctx *)ctx;

	if (ctx->written > sctx->size)
		return 0;

	const int remain = size < sctx->size - ctx->written
			? size : sctx->size - ctx->written;
	memcpy(sctx->buf + ctx->written, buf, remain);

	return 0;
}

int vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
	struct print_str_ctx ctx = {
		.ctx = {.out = &str_out},
		.buf = buf,
		.size = (int)size
	};
	const int rc = __vprintf(&ctx.ctx, fmt, args);

	if (rc >= 0)
		buf[rc < (int)size ? rc : (int)size - 1] = '\0';
	return rc;
}

int printf(const char *fmt, ...)
{
	va_list args;
	int rc;

	va_start(args, fmt);
	rc = vprintf(fmt, args);
	va_end(args);

	return rc;
}

int snprintf(char *buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int rc;

	va_start(args, fmt);
	rc = vsnprintf(buf, size, fmt, args);
	va_end(args);

	return rc;
}
