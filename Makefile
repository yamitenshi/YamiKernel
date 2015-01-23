all:
	nasm -f elf32 src/boot.s -o bin/boot.o
	ld -T src/link.ld -melf_i386 bin/boot.o -o bin/kernel.bin

clean:
	@rm -f bin/*.o

distclean: clean
	@rm -f bin/kernel.bin
