#include <AOS-unix/printk.h>
#include <AOS-unix/string.h>
#include <AOS-unix/keyboard.h>

char tty_buffer[1024];

static void run_command(char *str)
{
	printk("\nYour message: %s\n", str);
}

void shell(char symbol, uint8_t scancode)
{
	static uint32_t count = 0;

	if (scancode == ENTER) {
		tty_buffer[count] = '\0';
		run_command(tty_buffer);
		memset(tty_buffer, '\0', sizeof(tty_buffer));
		count = 0;
		printk("AOS-unix_root> ");
	} else if (scancode == BACKSPACE && count) {
			monitor_backspace();
			--count;
	} else if (scancode != BACKSPACE) {
		monitor_put_char(symbol);
		tty_buffer[count++] = symbol;
	}
}