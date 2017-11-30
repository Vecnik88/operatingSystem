#include <AOS-unix/keyboard.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/tty.h>

/* состояние клавиатуры */
int _kkybrd_disable = 1;
int _numlock = 0;
int _scrolllock = 0;
int _capslock = 0;

/* команды для контроллера клавиатуры на материнской плате */
enum KYBRD_ENCODER_IO {
	KYBRD_ENC_INPUT_BUF	= 0x60,
	KYBRD_ENC_CMD_REG	= 0x60
};

/* управляющие команды для контроллера клавиатуры */
enum KYBRD_ENC_CMDS {
	KYBRD_ENC_CMD_SET_LED				=	0xED,
	KYBRD_ENC_CMD_ECHO					=	0xEE,
	KYBRD_ENC_CMD_SCAN_CODE_SET			=	0xF0,
	KYBRD_ENC_CMD_ID					=	0xF2,
	KYBRD_ENC_CMD_AUTODELAY				=	0xF3,
	KYBRD_ENC_CMD_ENABLE				=	0xF4,
	KYBRD_ENC_CMD_RESETWAIT				=	0xF5,
	KYBRD_ENC_CMD_RESETSCAN				=	0xF6,
	KYBRD_ENC_CMD_ALL_AUTO				=	0xF7,
	KYBRD_ENC_CMD_ALL_MAKEBREAK			=	0xF8,
	KYBRD_ENC_CMD_ALL_MAKEONLY			=	0xF9,
	KYBRD_ENC_CMD_ALL_MAKEBREAK_AUTO	=	0xFA,
	KYBRD_ENC_CMD_SINGLE_AUTOREPEAT		=	0xFB,
	KYBRD_ENC_CMD_SINGLE_MAKEBREAK		=	0xFC,
	KYBRD_ENC_CMD_SINGLE_BREAKONLY		=	0xFD,
	KYBRD_ENC_CMD_RESEND				=	0xFE,
	KYBRD_ENC_CMD_RESET					=	0xFF
};

/* команды для контроллера клавиатуры на клавиатуре */
enum KYBRD_CTRL_IO {
	KYBRD_CTRL_STATS_REG	= 0x64,
	KYBRD_CTRL_CMD_REG		= 0x64
};

/* Маски для чтения и записи в регистр состояния */
enum KYBRD_CTRL_STATS_MASK {
	KYBRD_CTRL_STATS_MASK_OUT_BUF	= 1,		// 00000001
	KYBRD_CTRL_STATS_MASK_IN_BUF	= 2,		// 00000010
	KYBRD_CTRL_STATS_MASK_SYSTEM	= 4,		// 00000100
	KYBRD_CTRL_STATS_MASK_CMD_DATA	= 8, 	// 00010000
	KYBRD_CTRL_STATS_MASK_LOCKED	= 0x10,	// 00010000
	KYBRD_CTRL_STATS_MASK_AUX_BUF	= 0x20, 	// 00100000
	KYBRD_CTRL_STATS_MASK_TIMEOUT	= 0x40,	// 01000000
	KYBRD_CTRL_STATS_MASK_PARITY 	= 0x80		// 10000000
};

enum KYBRD_CTRL_CMDS {
	KYBRD_CTRL_CMD_READ				=	0x20,
	KYBRD_CTRL_CMD_WRITE			=	0x60,
	KYBRD_CTRL_CMD_SELF_TEST		=	0xAA,
	KYBRD_CTRL_CMD_INTERFACE_TEST	=	0xAB,
	KYBRD_CTRL_CMD_DISABLE			=	0xAD,
	KYBRD_CTRL_CMD_ENABLE			=	0xAE,
	KYBRD_CTRL_CMD_READ_IN_PORT		=	0xC0,
	KYBRD_CTRL_CMD_READ_OUT_PORT	=	0xD0,
	KYBRD_CTRL_CMD_WRITE_OUT_PORT	=	0xD1,
	KYBRD_CTRL_CMD_READ_TEST_INPUTS	=	0xE0,
	KYBRD_CTRL_CMD_SYSTEM_RESET		=	0xFE,
	KYBRD_CTRL_CMD_MOUSE_DISABLE	=	0xA7,
	KYBRD_CTRL_CMD_MOUSE_ENABLE		=	0xA8,
	KYBRD_CTRL_CMD_MOUSE_PORT_TEST	=	0xA9,
	KYBRD_CTRL_CMD_MOUSE_WRITE		=	0xD4
};

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
    
    shell(get_char());
    /*if (scancode == BACKSPACE) {
        monitor_backspace();
    } else if (scancode == ENTER) {
        monitor_put_char('\n');
    } else {
        shell(get_char());
    }*/
}

uint8_t get_scan_code()
{
    char c = 0;

        if (in_byte(KYBRD_ENC_INPUT_BUF) != c) {
            c = (char)in_byte(KYBRD_ENC_INPUT_BUF);
            
            if(c > 0)
                return c;
        }
}

uint8_t get_char()
{
    return scancode[get_scan_code()];
}

/* возвращает состояние контроллера клавиатуры */
uint8_t kybrd_ctrl_read_status()
{
	return in_byte(KYBRD_CTRL_STATS_REG);
}

/* отправляем команду на контроллер клавиатуры */
void kybrd_ctrl_send_cmd(uint8_t cmd)
{
	while(1) {
		/* когда внутренний буфер будет свободен, тогда и отправим */
		if (kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF == 0)
			break;
	}

	out_byte(KYBRD_ENC_CMD_REG, cmd);
}

/* устанавливаем светодиоды на клавиатуре */
void kkybrd_set_leds(bool num, bool caps, bool scroll)
{
	uint8_t data = 0;

	/* установить или очистить бит */
	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);

	kybrd_ctrl_send_cmd(KYBRD_ENC_CMD_SET_LED);
	kybrd_ctrl_send_cmd(data);
}

uint8_t kybrd_enc_read_buf()
{
	return in_byte(KYBRD_ENC_INPUT_BUF);
}

/* 
	самотестирование клавиатуры 
	если 1, то тест пройден
	если 0, то имеются неполадки
*/
int kkybrd_self_test()
{
	kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_SELF_TEST);

	while(1) {
		if (kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF)
			break;

		return (kybrd_enc_read_buf() == 0x55) ? 1 : 0;
	}
}

static void kkybrd_disable()
{
	KYBRD_CTRL_CMD_DISABLE;
	_kkybrd_disable = 1;
}

static void kkybrd_enable()
{
	kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_ENABLE);
	_kkybrd_disable = 0;
}

void init_keyboard()
{
	register_interrupt_handler(IRQ1, keyboard_callback);

	if (kkybrd_self_test) {
		kkybrd_enable();
	}
	else {
		kkybrd_disable();
		printk("keyboard is not run\n");
		return;
	}

	_numlock = _scrolllock = _capslock = 0;
	kkybrd_set_leds(_numlock, _scrolllock, _capslock);

	printk("keyboard init\n");
}
