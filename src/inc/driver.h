#ifndef DRIVER_H_
#define DRIVER_H_

#include "io.h"
#include "framebuffer.h"
#include "colors.h"

typedef struct {
    unsigned short x;
    unsigned short y;
} __attribute__((packed)) position;

position cursor_pos = { .x = 0, .y = 0 };

void putCharAtPos(char c, position pos, color col) {
    unsigned int position = (FB_WIDTH*pos.y) + pos.x;
    fb_write_cell(2*position, c, col.fg, col.bg);
}

void setCursorPos(position pos) {
    cursor_pos.x = pos.x;
    cursor_pos.y = pos.y;

    fb_move_cursor((cursor_pos.y*FB_WIDTH)+cursor_pos.x);
}

void write(char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    color col = { .fg = fg, .bg = bg };

    for(unsigned int i = 0; i < len; i++) {
        if(buf[i] != '\n') {
            putCharAtPos(buf[i], cursor_pos, col);
            cursor_pos.x++;
            if(cursor_pos.x >= FB_WIDTH) {
                cursor_pos.y++;
                cursor_pos.x = 0;
            }
        } else {
            cursor_pos.y++;
            cursor_pos.x = 0;
        }

        if(cursor_pos.y >= FB_HEIGHT) {
            cursor_pos.y = 0;
        }
    }
    setCursorPos(cursor_pos);
}

#endif
