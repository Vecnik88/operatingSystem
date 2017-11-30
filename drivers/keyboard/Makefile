# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

CC?=gcc
GDB?=gdb

CFLAGS=-g -ffreestanding -m32 -O0 -I$(INC)
LDLFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

INC=../../include

all:
	@echo -n "drivers/keyboard/keyboard.o " >> ../../objs.txt
	$(CC) $(CFLAGS) -c keyboard.c -o keyboard.o

clean:
	-@rm *.o