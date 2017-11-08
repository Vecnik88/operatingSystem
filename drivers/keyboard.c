#include <AOS-unix/keyboard.h>
#include <AOS-unix/printk.h>

uint8_t get_char();
uint8_t get_scan_code();

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    	"7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar" };

const char scancode[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    	'7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' ' };

static void keyboard_callback(registers_t regs)
{
	uint8_t scancode = get_scan_code();
    
    if (scancode > SC_MAX)
    	return;
    
    if (scancode == BACKSPACE) {
        monitor_backspace();
    } else if (scancode == ENTER) {
        monitor_put_char('\n');
    } else {
        char letter = get_char();
        
        monitor_put_char(letter);
    }
}

void init_keyboard()
{
	register_interrupt_handler(IRQ1, keyboard_callback);
	printk("keyboard init\n");
}

uint8_t get_scan_code()
{
    char c = 0;

        if (in_byte(0x60) != c) {
            c = (char)in_byte(0x60);
            
            if(c > 0)
                return c;
        }
}

uint8_t get_char()
{
    return scancode[get_scan_code()];
}