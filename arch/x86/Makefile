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

INC:=../../include

all:
	@echo -n "arch/x86/cpuid.o arch/x86/panic.o arch/x86/boot.o ">> ../../objs.txt

	$(CC) $(CFLAGS) -c cpuid.c -o cpuid.o
	$(CC) $(CFLAGS) -c panic.c -o panic.o
	$(AS) $(ASFLAGS) boot.s -o boot.o
	@cd hal && $(MAKE) $(MFLAGS)

clean:
	-@rm -rf *.o
	@cd hal && $(MAKE) clean