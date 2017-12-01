#include <AOS-unix/printk.h>
#include <AOS-unix/string.h>
#include <AOS-unix/keyboard.h>
#include <AOS-unix/cpuid.h>

char tty_buffer[1024];
char **command = {
	"END", 
	"CPUID",
	"ECHO"
};

static void computer_off()
{
	asm volatile("cli");
	asm volatile("hlt");
}

void echo_command(char *str)
{
	int i = 5;
	while(str[i])
		monitor_put_char(str[i++]);
}

void incorrect_cmd()
{
	printk("\n Incorrect command\n");
}

static void run_command(char *str)
{
	int i, j;
	for (i = 0; i < sizeof(command); ++i) {
		for (j = 0; j < sizeof(str); ++j) {
			if (str[j] == command[i][j]) {
				while(str[j]) {
					if (str[j] == command[i][j++])
						continue;
					else
						break;
				}
				switch(i) {
					case 0: computer_off(); return;
					case 1: print_info_cpu(); return;
					case 2: echo_command(str); return;
					default: incorrect_cmd(); return;
				}
			} else {
				break;
			}
		}
	}
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