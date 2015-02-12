#ifndef IO_H_
#define IO_H_

/*
 * outb: Send the given data to the I/O port. Defined in io.s
 * port: The I/O port to send the data to
 * data: The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif
