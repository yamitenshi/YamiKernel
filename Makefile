CC=gcc
CC_FLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra
ASM=nasm
ASM_FLAGS=-f elf32
LD=ld
LD_FLAGS=-T src/link.ld -melf_i386

kernel:
	${ASM} ${ASM_FLAGS} src/boot.s -o bin/boot.o
	${LD} ${LD_FLAGS} bin/boot.o -o bin/kernel.bin

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
