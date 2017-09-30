#include "../drivers/ports.h"

/* start kernel */
void main(void)
{
	out_byte(0x3d4, 14);
	u32_int position = in_byte(0x3d5);
	position = position << 8;

	out_byte(0x3d4, 15);
	position += in_byte(0x3d5);

	u32_int offset_from_vga = position * 2;

	s8_int* vga = 0xb8000;
	vga[offset_from_vga] = 'X';
	vga[offset_from_vga + 1] = 0x0f;
}