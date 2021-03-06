# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

CC?=gcc
GDB?=gdb
LD?=ld

CFLAGS:=-g -ffreestanding -m32 -O0 -I$(INC)
LDLFLAGS:=-Tlink.ld -melf_i386
ASFLAGS:=-felf

INC:=../include
SRC:=./boot ./kernel ./memory ./cpu ./drivers ./libc

C_SOURCES:=$(shell find $(SRC)/*.c)
C_OBJECTS:=$(C_SOURCES:.c=.o)
S_SOURCES:=$(shell find $(SRC)/*.s)
S_OBJECTS:=$(S_SOURCES:.s=.o)
OBJ:=$(C_OBJECTS) $(S_OBJECTS)

all: kernel

# собираем наше ядро(без загрузчика)
kernel: $(OBJ)
	$(LD) $(LDLFLAGS) -o $@ $(OBJ)

# делаем объектные файлы из файлов на ассемблере
$(S_OBJECTS): %.o: %.s
	nasm $< -f elf -o $@

# делаем объектные файлы из файлов на С
$(C_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	qemu-system-x86_64 -kernel kernel -m 512M

debug: kernel
	qemu-system-x86_64 -s -kernel kernel &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel"

.PHONY: clean
clean:
	-rm *.o kernel

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