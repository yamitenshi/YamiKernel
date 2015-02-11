#ifndef DRIVER_H_
#define DRIVER_H_

#include "io.h"
#include "framebuffer.h"

int write(char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    static unsigned int cursor_pos = 0;

    for(unsigned int i = 0; i < len; i++) {
        if(buf[i] != '\n') {
            fb_write_cell(2*cursor_pos, buf[i], fg, bg);
        } else {
            unsigned int cursor_line = (unsigned int)(cursor_pos/80) + 1;
            cursor_pos = cursor_line*80;
        }

        cursor_pos++;
        cursor_pos %= (80*25)-1;
    }
    fb_move_cursor(cursor_pos);

    return cursor_pos;
}

#endif
