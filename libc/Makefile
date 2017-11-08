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


all:
	echo -n "libc/mem.o libc/string.o " >> objs.txt
	$(CC) $(CFLAGS) -c string.c -o string.o

clean:
	-rm *.o