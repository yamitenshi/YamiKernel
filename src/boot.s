; YamiKernel boot assembly file

global loader                   ; The entry symbol for ELF

MAGIC        equ 0x1BADB002     ; The magic number required for multiboot
FLAGS        equ 0x0            ; Multiboot flags
CHECKSUM     equ -(MAGIC+FLAGS) ; Checksum calculation

KERNEL_STACK_SIZE equ 4096      ; Define kernel stack size

section .text                   ; Start of the text section
align 4                         ; Code must be 4 byte aligned
    dd MAGIC                    ; Write the magic number to the machine code
    dd FLAGS                    ; Same with the flags
    dd CHECKSUM                 ; Same with the checksum

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE      ; Reserve a 4 KiB stack for the kernel

loader:                         ; The loader label (defined as entry point)
    mov esp, kernel_stack + KERNEL_STACK_SIZE

.loop:
    jmp .loop                   ; Loop forever
