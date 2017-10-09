#include "../cpu/types.h"

#define MULTIBOOT_FLAG_MEM		0x001
#define MULTIBOOT_FLAG_DEVICE	0x002
#define MULTIBOOT_FLAG_CMDLINE	0x004
#define MULTIBOOT_FLAG_MODS		0x008
#define MULTIBOOT_FLAG_AOUT		0x010
#define MULTIBOOT_FLAG_ELF		0x020
#define MULTIBOOT_FLAG_MMAP		0x040
#define MULTIBOOT_FLAG_CONFIG	0x080
#define MULTIBOOT_FLAG_LOADER	0x100
#define MULTIBOOT_FLAG_APM		0x200
#define MULTIBOOT_FLAG_VBE		0x400

struct multiboot {
	u32_int flags;
	u32_int mem_lower;
	u32_int mem_upper;
	u32_int boot_device;
	u32_int cmdline;
	u32_int mods_count;
	u32_int mods_addr;
	u32_int num;
	u32_int size;
	u32_int addr;
	u32_int shndx;
	u32_int mmap_length;
	u32_int mmap_addr;
	u32_int drives_length;
	u32_int drives_addr;
	u32_int config_table;
	u32_int boot_loader_name;
	u32_int apm_table;
	u32_int vbe_control_info;
	u32_int vbe_mode_info;
	u32_int vbe_mode;
	u32_int vbe_interface_seg;
	u32_int vbe_interface_off;
	u32_int vbe_interface_len;
} __attribute__((packed));

typedef struct multiboot_header multiboot_header_t;