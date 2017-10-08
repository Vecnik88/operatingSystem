#include "fs.h"

fs_node_t* fs_root = 0;

u32_int read_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
	if (node->read != 0)
		return node->read(node, offset, size, buffer);
	else
		return 0;
}
