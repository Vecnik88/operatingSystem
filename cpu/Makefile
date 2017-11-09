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
ASFLAGS=-felf

INC:=../include

all:
	@echo -n "cpu/cpuid.o cpu/gdt.o cpu/interrupt.o cpu/panic.o \
			 cpu/descriptor_tables.o cpu/idt.o cpu/isr.o " >> ../objs.txt

	$(CC) $(CFLAGS) -c cpuid.c -o cpuid.o
	$(CC) $(CFLAGS) -c descriptor_tables.c -o descriptor_tables.o
	$(CC) $(CFLAGS) -c idt.c -o idt.o
	$(CC) $(CFLAGS) -c isr.c -o isr.o
	$(CC) $(CFLAGS) -c panic.c -o panic.o
	$(AS) gdt.s -f elf -o gdt.o
	$(AS) interrupt.s -f elf -o interrupt.o

clean:
	-@rm *.o