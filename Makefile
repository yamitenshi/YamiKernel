kernel:
	nasm -f elf32 src/boot.s -o bin/boot.o
	ld -T src/link.ld -melf_i386 bin/boot.o -o bin/kernel.bin

clean:
	@rm -f bin/*.o

distclean: clean
	@rm -f bin/kernel.bin bin/iso/boot/kernel.bin bin/yamikernel.iso

isoimage: kernel
	@cp bin/kernel.bin bin/iso/boot
	@genisoimage -R \
				 -b boot/grub/stage2_eltorito \
				 -no-emul-boot \
				 -boot-load-size 4 \
				 -A YamiKernel \
				 -input-charset utf8 \
				 -quiet \
				 -boot-info-table \
				 -o bin/yamikernel.iso \
				 bin/iso

all: kernel isoimage
