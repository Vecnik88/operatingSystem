#include <AOS-unix/interrupt.h>

void divide_by_zero_fault(uint32_t eip, uint32_t cs, uint32_t flags) {
	intstart();
	printk("Divide by 0 at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void _cdecl single_step_trap(uint32_t cs, uint32_t eip, uint32_t flags) {
	intstart();
	printk("Single step at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void _cdecl nmi_trap(uint32_t cs, uint32_t eip, uint32_t flags) {
	intstart();
	kernel_panic ("NMI trap at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void _cdecl breakpoint_trap (uint32_t cs, uint32_t eip, uint32_t flags) {
	intstart();
	printk("Breakpoint trap at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void overflow_trap(uint32_t cs, uint32_t eip, uint32_t flags) {
	intstart ();
	printk("Overflow trap at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void bounds_check_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {
	intstart();
	printk("Bounds check fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void invalid_opcode_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {
	intstart ();
	printk("Invalid opcode at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void no_device_fault (uint32_t cs, uint32_t eip, uint32_t flags) {
	intstart ();
	printk("Device not found fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void double_fault_abort (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	intstart();
	printk("Double fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void invalid_tss_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	intstart ();
	printk("Invalid TSS at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void no_segment_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	intstart ();
	kernel_panic ("Invalid segment at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void _cdecl stack_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	intstart();
	kernel_panic ("Stack fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

void _cdecl general_protection_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {
	intstart();
	printk("General Protection Fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",
		cs,cs, cs);
	for (;;);
}


//! page fault
void _cdecl page_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {

	intstart ();

	int faultAddr=0;

	_asm {
		mov eax, cr2
		mov [faultAddr], eax
	}

	kernel_panic ("Page Fault at 0x%x:0x%x refrenced memory at 0x%x",
		cs, eip, faultAddr);
	for (;;);
}

//! Floating Point Unit (FPU) error
void interrupt _cdecl fpu_fault  (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	intstart ();
	kernel_panic ("FPU Fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

//! alignment check
void interrupt _cdecl alignment_check_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	intstart ();
	kernel_panic ("Alignment Check at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

//! machine check
void interrupt _cdecl machine_check_abort  (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	intstart ();
	kernel_panic ("Machine Check at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}

//! Floating Point Unit (FPU) Single Instruction Multiple Data (SIMD) error
void interrupt _cdecl simd_fpu_fault (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	intstart ();
	kernel_panic ("FPU SIMD fault at physical address [0x%x:0x%x] EFLAGS [0x%x]",cs,eip, flags);
	for (;;);
}
