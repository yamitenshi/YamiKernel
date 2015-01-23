; YamiKernel boot assembly file

global loader                   ; The entry symbol for ELF

MAGIC        equ 0x1BADB002     ; The magic number required for multiboot
FLAGS        equ 0x0            ; Multiboot flags
CHECKSUM     equ -(MAGIC+FLAGS) ; Checksum calculation

section .text                   ; Start of the text section
align 4                         ; Code must be 4 byte aligned
    dd MAGIC                    ; Write the magic number to the machine code
    dd FLAGS                    ; Same with the flags
    dd CHECKSUM                 ; Same with the checksum

loader:                         ; The loader label (defined as entry point)
    mov eax, 0xCAFEBABE         ; Place 0xCAFEBABE in register eax

.loop:
    jmp .loop                   ; Loop forever
