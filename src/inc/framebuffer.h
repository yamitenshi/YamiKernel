#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "io.h"

#define FB_WIDTH    80
#define FB_HEIGHT   25

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

char *fb = (char*)0x000B8000;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4) | (fg & 0x0f);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (char)((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (char)(pos & 0x00FF));
}

#endif
