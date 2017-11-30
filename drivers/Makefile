# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила

CC?=gcc
GDB?=gdb

CFLAGS=-g -ffreestanding -m32 -O0 -I$(INC)
LDLFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

INC=../include

all:
	@echo -n "drivers/port.o drivers/timer.o drivers/printk.o " >> ../objs.txt
	$(CC) $(CFLAGS) -c port.c -o port.o
	$(CC) $(CFLAGS) -c timer.c -o timer.o
	$(CC) $(CFLAGS) -c printk.c -o printk.o
	@cd display && $(MAKE) $(MFLAGS)
	@cd keyboard && $(MAKE) $(MFLAGS) 

clean:
	-@rm *.o