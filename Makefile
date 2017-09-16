all: run

kernel.bin: kernel_entry.o kernel.o
	ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -ffreestanding -c $< -o $@

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: bootsect.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat kernel.bin > os-image.bin

run: os-image.bin
	qemu-system-x86_64 -fda $<

clean:
	rm *.bin *.o *.dis