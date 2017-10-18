#include "../cpu/isr.h"
#include "../drivers/monitor.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../memory/heap.h"
#include "../memory/bootmem.h"
/*#include "../fs/multiboot.h"
#include "../fs/fs.h"
#include "../fs/initrd.h"*/

/* start kernel */
int main()
{
	//k_print("                    Operations system Unix-0.0.1 load\n");
 	isr_init();
 	irq_init();
 	clear_screen();
 	k_print("Hello user :)\n");

	/*init_pmm(0x10000000);
 	init_vmm();
 	init_heap();*/


   	    // Initialise all the ISRs and segmentation
    //init_descriptor_tables();
    // Initialise the screen (by clearing it)
    //monitor_clear();

    // Find the location of our initial ramdisk.
    /*ASSERT(mboot_ptr->mods_count > 0);
    u32_int initrd_location = *((u32_int*)mboot_ptr->mods_addr);
    u32_int initrd_end = *(u32_int*)(mboot_ptr->mods_addr+4);
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;
    bootmem_init(0x80000000);

    // Initialise the initial ramdisk, and set it as the filesystem root.
    fs_root = initialise_initrd(initrd_location);

    // list the contents of /
    int i = 0;
    struct dirent *node = 0;
    while ( (node = readdir_fs(fs_root, i)) != 0)
    {
        k_print("Found file ");
        k_print(node->name);
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);

        if ((fsnode->flags&0x7) == FS_DIRECTORY)
        {
            k_print("\n\t(directory)\n");
        }
        else
        {
            k_print("\n\t contents: \"");
            char buf[256];
            u32_int sz = read_fs(fsnode, 0, 256, buf);
            int j;
            for (j = 0; j < sz; j++)
                monitor_put(buf[j]);
            
            k_print("\"\n");
        }
        i++;
    }

    return 0;*/
}

void user_input(s8_int* input)
{
    if (strcmp(input, "END") == 0) {
        k_print("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    }
    k_print("You said: ");
    k_print(input);
    k_print("\n> ");
}