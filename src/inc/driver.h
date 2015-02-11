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

void clearScreen(color col) {
    for(unsigned short x = 0; x < FB_WIDTH; x++) {
        for(unsigned short y = 0; y < FB_HEIGHT; y++) {
            position pos = { .x = x, .y = y };
            putCharAtPos(' ', pos, col);
        }
    }
    setCursorPos((position) { .x = 0, .y = 0 });
}

void write(char *buf, color col) {
    unsigned short i = 0;

    while(buf[i] != '\0') {
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
        i++;
    }

    setCursorPos(cursor_pos);
}

#endif