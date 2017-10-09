#include "fs.h"

fs_node_t* fs_root = 0;

u32_int read_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
	if (node->read)
		return node->read(node, offset, size, buffer);

	return 0;
}

u32_int write_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
	if (node->write)
		return node->write(node, offset, size, buffer);

	return 0;
}

void open_fs(fs_node_t* node, u8_int read, u8_int write)
{
	if (node->open)
		return node->open(node, read, write);
}

void close_fs(fs_node_t* node)
{
	if (node->close != 0)
		return node->close(node);
}

struct dirent *readdir_fs(fs_node_t *node, u32int index)
{
	if ((node->flags&0x7) == FS_DIRECTORY && node->readdir != 0 )
			return node->readdir(node, index);
	
	return 0;
}

fs_node_t* finddir_fs(fs_node_t* node, s8_int* name)
{
	if ((node->flags&0x7) == FS_DIRECTORY && node->finddir != 0 )
			return node->finddir(node, name);
	
	return 0;
}