#include <AOS-unix/panic.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>

extern void panic(const char *message, const char *file, uint32_t line)
{
    asm volatile("cli");

    printk("PANIC(");
    printk(message);
    printk(") at ");
    printk(file);
    printk(":");
    monitor_write_dec(line);
    printk("\n");
    
    for(;;);
}

extern void panic_assert(const char *file, uint32_t line, const char *desc)
{
    asm volatile("cli");

    printk("ASSERTION-FAILED(");
    printk(desc);
    printk(") at ");
    printk(file);
    printk(":");
    monitor_write_dec(line);
    printk("\n");

    for(;;);
}
