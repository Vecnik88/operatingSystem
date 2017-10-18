#include "fs.h"

fs_node_t* fs_root = (void*) 0;

u32int read_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
    if (node->read != 0)
        return node->read(node, offset, size, buffer);
    else
        return 0;
}

u32int write_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
    if (node->write != 0)
        return node->write(node, offset, size, buffer);
    else
        return 0;
}

void open_fs(fs_node_t* node, u8_int read, u8_int write)
{
    if (node->open != 0)
        return node->open(node);
}

void close_fs(fs_node_t* node)
{
    if (node->close != 0)
        return node->close(node);
}

struct dirent* readdir_fs(fs_node_t* node, u32_int index)
{
    if ((node->flags & 0x7) == FS_DIRECTORY &&
         node->readdir != 0)
        return node->readdir(node, index);
    else
        return 0;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
    if ( (node->flags & 0x7) == FS_DIRECTORY &&
         node->finddir != 0)
        return node->finddir(node, name);
    else
        return 0;
}