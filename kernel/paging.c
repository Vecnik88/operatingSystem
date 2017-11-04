#include <AOS-unix/paging.h>
#include <AOS-unix/kheap.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/string.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/panic.h>

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

extern uint32_t placement_address;

/* таблица фреймов ядра */
page_directory_t *kernel_directory = 0;

/* таблица фреймов текущей директории */
page_directory_t *current_directory = 0;

/* состояние фреймов */
uint32_t *frames;
uint32_t nframes;

/* функция для установки бита в наборе bitset для фреймов */
static void set_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   
   frames[idx] |= (0x1 << off);
}

/* функция для сброса бита в наборе bitset для фреймов */
static void clear_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   
   frames[idx] &= ~(0x1 << off);
}

/* функция для проверки, установлен ли бит*/
static uint32_t test_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   
   return (frames[idx] & (0x1 << off));
}

/* Статическая функция для поиска первого свободного фрейма */
static uint32_t first_frame()
{
   uint32_t i, j;
   for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
   {
       if (frames[i] != 0xffffffff) {// ничего не освобождаем, сразу выходим.
           // по меньшей мере, здесь один свободный бит
           for (j = 0; j < 32; j++) {
               uint32_t to_test = 0x1 << j;
               
               if (!(frames[i] & to_test)) {
                   return i * 4 * 8 + j;
               }
           }
       }
   }
}

/* функция выделения фрейма */
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
   if (page->frame != 0) {
       return; // фрейм уже выделен
   } else {
       uint32_t idx = first_frame(); // idx теперь является индексом первого свободного фрейма.

       if (idx == (uint32_t)-1)
           PANIC("No free frames!");

       set_frame(idx*0x1000); 				// Этот фрейм теперь наш!
       page->present = 1; 					// Помечаем его как присутствующий.
       page->rw = (is_writeable)? 1 : 0; 	// Можно ли для страницы выполнять запись?
       page->user = (is_kernel) ? 0 : 1; 	// Находится ли страница в пользовательском режиме?
       page->frame = idx;
   }
}

/* функция освобождения фоейма */
void free_frame(page_t *page)
{
   uint32_t frame;
   if (!(frame = page->frame)) {
       return; 								// указанной страницы нет в выделенном фрейме
   } else {
       clear_frame(frame);					// фрейм теперь снова свободен.
       page->frame = 0x0;					// cтраницы теперь во фрейме нет.
   }
}

void init_paging()
{
	uint32_t mem_end_page = 0x1000000;
	nframes = mem_end_page / 0x1000;
	frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(nframes));
	
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	kernel_directory = (page_directory_t *)kmalloc(sizeof(page_directory_t));

	memset(kernel_directory, 0, sizeof(page_directory_t));

	current_directory = kernel_directory;

	/**
		нам нужна карта идентичности (физический адрес = виртуальный адрес) с адреса
		0x0 до конца используемой памяти с тем, чтобы у нас к ним был прозрачный 
		доступ как если бы страничная организация памяти не использовалась.

		внутри тела цикла мы фактически изменяем адрес placement_address
		с помощью вызова функции kmalloc(). Цикл while используется здесь, т.к. выход
		из цикла динамически, а не один раз после запуска цикла.
	 **/

	int i = 0;
	while (i < placement_address) {
       /* код ядра можно читать из пользовательского режима, но нельзя в него записывать */
       alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
       i += 0x1000;
   }
	/**
   		прежде, чем включить страничное управление памятью, нужно зарегистрировать
   		обработчик некорректного обращения к памяти - page fault.
	**/
	register_interrupt_handler(ISR14, page_fault);

	/* включаем страничную организацию памяти */
	switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	asm volatile("mov %0, %%cr3" : : "r"(&dir->tables_physical));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r"(cr0));

	cr0 |= 0x80000000; 			// включаем paging
	for(;;)
	asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir)
{
	/* Помещаем адрес в индекс */
	address /= 0x1000;
	/* находим таблицу страниц, в которой есть этот адрес */
	uint32_t table_idx = address / 1024;
   
	if (dir->tables[table_idx]) {// Если эта таблица уже назначена
       return &dir->tables[table_idx]->pages[address%1024];
	} else if(make) {
       uint32_t tmp;
       dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
       memset(dir->tables[table_idx], 0, 0x1000);
       dir->tables_physical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
       
       return &dir->tables[table_idx]->pages[address%1024];
	} else {
       return 0;
	}
}

void page_fault(registers_t regs)
{
	/**
		возникло прерывания неверного обращения к странице - page fault.
		адрес прерывания запоминается в регистре CR2.
	 **/

	uint32_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	/* Код ошибки подробно сообщит нам о том, что случилось */
	int present = !(regs.err_code & 0x1);		// страница отсутствует
	int rw = regs.err_code & 0x2;				// операция записи?
	int us = regs.err_code & 0x4;				// процессор находится в пользовательском режиме?
	int reserved = regs.err_code & 0x8;			// в записи страницы переписаны биты, зарезервированные для нужд процессора?
	int id = regs.err_code & 0x10;				// причина во время выборки инструкции?

	/* выдача сообщения об ошибке */
	printk("Page fault! ( ");
	
	if (present) 
		printk("present ");
	
	if (rw) 
		printk("read-only ");
	
	if (us) 
		printk("user-mode ");

	if (reserved) 
		printk("reserved ");

	printk(") at 0x");
	monitor_write_hex(faulting_address);
	printk("\n");
	
	PANIC("Page fault");
} 
