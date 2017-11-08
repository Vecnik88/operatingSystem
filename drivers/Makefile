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
	echo -n "drivers/port.o drivers/timer.o " >> ../objs.txt
	$(CC) $(CFLAGS) -c port.c -o port.o
	$(CC) $(CFLAGS) -c timer.c -o timer.o
	cd monitor && $(MAKE) $(MFLAGS) 

clean:
	-rm *.o