# Makefile по сборке AOS
# $@ Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
# $^ Список всех зависимостей обрабатываемого правила
.PHONY: clean bkernel

all: bkernel link run

CC?=gcc
GDB?=gdb
LD?=ld

CFLAGS:=-g -ffreestanding -m32 -O0
LDLFLAGS:=-Tlink.ld -melf_i386
ASFLAGS:=-felf

# сборка объектных файлов из исходников
bkernel:
	@$(MAKE) clean
	@echo "Start build kernel"
	if [[ -e "objs.txt" ]]; then -rm objs.txt; fi;
	@cd arch/x86/ && $(MAKE) $(MFLAGS)
	@cd kernel && $(MAKE) $(MFLAGS)
	@cd memory && $(MAKE) $(MFLAGS)
	@cd cpu && $(MAKE) $(MFLAGS)
	@cd drivers && $(MAKE) $(MFLAGS)
	@cd libc && $(MAKE) $(MFLAGS)

OBJ=`cat objs.txt`

# линковка объектных файлов
link:
	$(LD) $(LDLFLAGS) -o bkernel $(OBJ)
	@echo "Kernel done."

# запускаем qemu
run:
	qemu-system-x86_64 -kernel bkernel -m 256M

# подключаем отладчик
debug: bkernel
	qemu-system-x86_64 -s -kernel bkernel &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file bkernel"

# очищаем проект
clean:
	@cd arch/x86/ && $(MAKE) clean
	@cd kernel && $(MAKE) clean
	@cd memory && $(MAKE) clean
	@cd cpu && $(MAKE) clean
	@cd drivers && $(MAKE) clean
	@cd libc && $(MAKE) clean
	-@rm objs.txt
	-@rm bkernel
	@echo "Clear project with object file"
