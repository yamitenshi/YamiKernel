ENTRY(loader)               /* Name of the entry label          */

SECTIONS {
    . = 0x00100000;         /* Load code at 1MB                 */

    .text ALIGN (0x1000) :  /* Align at 4KB                     */
    {
        *(.text)            /* All text sections from all files */
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss ALIGN (0x1000) :
    {
        *(COMMON)
        *(.bss)
    }
}
