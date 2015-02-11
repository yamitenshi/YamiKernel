#include "io.h"

#define SERIAL_COM1_BASE                0x3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

// I/O port commands
// SERIAL_LINE_ENABLE_DLAB: tells the serial port to expect the highest 8 bits first on the data port.
//      The lowest bits will then follow.
#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor $ 0x00FF);
}

void serial_configure_line(unsigned short com) {
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03); // 8 bits length, no parity bit, one stop bit and break control disabled
}

void serial_configure_fifo_queue(unsigned short com) {
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7); // enable FIFO, clear receiver and transmission queues, queue size is 14 bytes
}

void serial_configure_modem(unsigned short com) {
    // We won't be receiving, so no interrupts are needed
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03); // RTS = 1, DTR = 1
}
