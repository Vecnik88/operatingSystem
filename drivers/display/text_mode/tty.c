#include <AOS-unix/printk.h>
#include <AOS-unix/string.h>
#include <AOS-unix/keyboard.h>
#include <AOS-unix/cpuid.h>

char tty_buffer[1024];

static int is_echo_cmd(char *str)
{
	int i = 0;
	if (str[i++] == 'E')
		if (str[i++] == 'C')
			if (str[i++] == 'H')
				if (str[i++] == 'O')
					if (str[i] == ' ')
						return 1;

	return 0;
}

static void computer_off()
{
	printk("computer_off");
	asm volatile("cli");
	asm volatile("hlt");
}

static void echo_command(char *str)
{
	monitor_put_char('\n');

	int i = 5;
	while(str[i])
		monitor_put_char(str[i++]);

	monitor_put_char('\n');
}

static void incorrect_cmd()
{
	printk("\n Incorrect command\n");
}

static void usage()
{
	printk("\nOS Development Series Keyboard Programming Demo");
	printk("\nwith a basic Command Line Interface (CLI)\n\n");
	printk("Supported commands:\n");
	printk(" - END: quits and halts the system\n");
	printk(" - CLS: clears the display\n");
	printk(" - HELP: displays this message\n");
	printk(" - CPUID: info with cpu\n");
}

static void run_command(char *str)
{
	if (strcmp(str, "CPUID") == 0)
		print_info_cpu();
	else if (is_echo_cmd(str))
		echo_command(str);
	else if (strcmp(str, "HELP") == 0)
		usage();
	else if (strcmp(str, "CLS") == 0)
		monitor_clear();
	else if (strcmp(str, "END") == 0)
		computer_off();
	else
		incorrect_cmd();
}

void shell(char symbol, uint8_t scancode)
{
	static uint32_t count = 0;

	if (scancode == ENTER) {
		tty_buffer[count] = '\0';
		if (count != 0)
			run_command(tty_buffer);
		
		memset(tty_buffer, '\0', sizeof(tty_buffer));
		count = 0;
		printk("\nAOS-unix_root> ");
	} else if (scancode == BACKSPACE && count) {
			monitor_backspace();
			--count;
	} else if (scancode != BACKSPACE) {
		monitor_put_char(symbol);
		tty_buffer[count++] = symbol;
	}
}