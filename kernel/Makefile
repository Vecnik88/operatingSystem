# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

CC=gcc
GDB=gdb
SOURCES = boot.o kernel.o port.o vga.o printk.o string.o \
			gdt.o interrupt.o isr.o descriptor_tables.o

CFLAGS=-g -ffreestanding -m32 -O0 -I$(INC) -I../
LDLFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

INC=../include

all: $(SOURCES) link

run:
	qemu-system-x86_64 -kernel kernel -m 512M

clean:
	-rm -rf *.o kernel

link:
	ld $(LDLFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $< -f elf -o $@

#nasm $(ASFLAGS) $<

#C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c memory/*.c)
#HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h memory/*.h)
# Nice syntax for file extension replacement
#OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
#CC = gcc
#GDB = gdb
# -g: Use debugging symbols in gcc
#CFLAGS = -g
# CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -g

# First rule is run by default
#os-image.bin: boot/bootsect.bin kernel.bin
#	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
#kernel.bin: boot/kernel_entry.o ${OBJ}
#	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
#kernel.elf: boot/kernel_entry.o ${OBJ}
#	ld -melf_i386 -o $@ -Ttext 0x1000 $^ 

#run: os-image.bin
#	qemu-system-x86_64 -kernel os-image.bin -m 512M
# qemu-system-x86_64 -fda os-image.bin -m 512M

# Open the connection to qemu and load our kernel-object file with symbols
#debug: os-image.bin kernel.elf
#	qemu-system-x86_64 -s -fda os-image.bin &
#	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
#%.o: %.c ${HEADERS}
#	${CC} -m32 ${CFLAGS} -ffreestanding -c $< -o $@

#%.o: %.asm
#	nasm $< -f elf -o $@

#%.bin: %.asm
#	nasm $< -f bin -o $@

#clean:
#	rm -rf *.bin *.dis *.o os-image.bin *.elf
#	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o memory/*.o