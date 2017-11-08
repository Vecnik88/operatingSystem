#include <AOS-unix/paging.h>
#include <AOS-unix/isr.h>
#include <AOS-unix/vga.h>
#include <stdint.h>

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

uint32_t page_directory[1024]__attribute__((aligned(4096)));
uint32_t first_page_table[1024]__attribute__((aligned(4096)));

void switch_page_directory(unsigned int *page_directory);
void page_fault(registers_t regs);

void paging_init()
{
	int i;
	for (i = 0; i < 1024; i++) {
		page_directory[i] = 0x00000002;
	}

	for (i = 0; i < 1024; i++) {
		first_page_table[i] = (i * 0x1000) | 3;
	}

	page_directory[0] = ((unsigned int)first_page_table) | 3;

	register_interrupt_handler(ISR14, page_fault);

	switch_page_directory(page_directory);
}

void switch_page_directory(unsigned int *page_directory)
{
   asm volatile("mov %0, %%cr3":: "r"(page_directory));
   uint32_t cr0;
   asm volatile("mov %%cr0, %0": "=r"(cr0));
   cr0 |= 0x80000000; // Enable paging!
   asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void page_fault(registers_t regs)
{
   // Возникло прерывания неверного обращения к странице - page fault.
   // Адрес прерывания запоминается в регистре CR2.
   uint32_t faulting_address;
   asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

   // Код ошибки подробно сообщит нам о том, что случилось.
   int present   = !(regs.err_code & 0x1); // Страница отсутствует
   int rw = regs.err_code & 0x2;           // Операция записи?
   int us = regs.err_code & 0x4;           // Процессор находится в пользовательском режиме?
   int reserved = regs.err_code & 0x8;     // В записи страницы переписаны биты, зарезервированные для нужд процессора?
   int id = regs.err_code & 0x10;          // Причина во время выборки инструкции?

   // Выдача сообщения об ошибке.
   monitor_write("Page fault! ( ");
   if (present) {monitor_write("present ");}
   if (rw) {monitor_write("read-only ");}
   if (us) {monitor_write("user-mode ");}
   if (reserved) {monitor_write("reserved ");}
   monitor_write(") at 0x");
   monitor_write_hex(faulting_address);
   monitor_write("\n");
   while (1){}
  // PANIC("Page fault");
} 
