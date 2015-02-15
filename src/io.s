global outb
global inb

; Send a byte to the I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] the return address
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

inb:
    mov dx, [esp + 4]
    in al, dx
    ret
