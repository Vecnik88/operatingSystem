#include <AOS-unix/printk.h>
#include <AOS-unix/string.h>
#include <AOS-unix/keyboard.h>

char tty_buffer[1024];
int new_str = 1;

static void run_command(char *str)
{
	printk("Your message: %s\n", str);
}

void shell(char symbol)
{
	if (new_str) {
		printk("AOS-unix-root > ");
		new_str = 0;
	}
	
	static uint32_t count = 0;

	if (symbol == ENTER) {
		tty_buffer[count] = '\0';
		memset(tty_buffer, '\0', sizeof(tty_buffer));
		new_str = 1;
		count = 0;
		run_command(tty_buffer);
	} else if (symbol == BACKSPACE) {
		monitor_backspace();
		--count;
	} else {
		monitor_put_char(symbol);
		tty_buffer[count++] = symbol;
	}
}