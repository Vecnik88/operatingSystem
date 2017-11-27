# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

CC?=gcc
GDB?=gdb
LD?=ld
AS=nasm

CFLAGS=-g -ffreestanding -m32 -O0 -I$(INC)
LDLFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-f elf

INC:=../../../include

all:
	@echo -n "arch/x86/hal/gdt.o arch/x86/hal/interrupt.o \
			  arch/x86/hal/descriptor_tables.o arch/x86/hal/idt.o \
			  arch/x86/hal/isr.o arch/x86/hal/hal.o " >> ../../../objs.txt

	$(CC) $(CFLAGS) -c descriptor_tables.c -o descriptor_tables.o
	$(CC) $(CFLAGS) -c hal.c -o hal.o
	$(CC) $(CFLAGS) -c idt.c -o idt.o
	$(CC) $(CFLAGS) -c isr.c -o isr.o
	$(AS) $(ASFLAGS) gdt.s -o gdt.o
	$(AS) $(ASFLAGS) interrupt.s -o interrupt.o

clean:
	-@rm -rf *.o