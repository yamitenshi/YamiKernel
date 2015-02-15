#ifndef DRIVER_H_
#define DRIVER_H_

#include "io.h"
#include "framebuffer.h"
#include "serial.h"
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

void copyCharToPos(position orig, position dest) {
    unsigned int pos_orig = (FB_WIDTH*orig.y) + orig.x;
    unsigned int pos_dest = (FB_WIDTH*dest.y) + dest.x;

    fb[pos_dest] = fb[pos_orig];
    fb[pos_dest+1] = fb[pos_orig+1];
}

void setCursorPos(position pos) {
    cursor_pos.x = pos.x;
    cursor_pos.y = pos.y;

    fb_move_cursor((cursor_pos.y*FB_WIDTH)+cursor_pos.x);
}

void scrollFramebuffer() {
    for(int y = 1; y < FB_HEIGHT; y++) {
        for(int x = 0; x < FB_WIDTH; x++) {
            position pos_orig = { .x = x, .y = y };
            position pos_dest = { .x = x, .y = y-1 };
            copyCharToPos(pos_orig, pos_dest);
        }
    }
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

        while(cursor_pos.y >= FB_HEIGHT) {
            scrollFramebuffer();
            cursor_pos.y = FB_HEIGHT - 1;
        }
        i++;
    }

    setCursorPos(cursor_pos);
}

void serial_write(char *buf) {
    static int serial_configured = 0;

    if(!serial_configured) {
        serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
        serial_configure_line(SERIAL_COM1_BASE);
        serial_configure_fifo_queue(SERIAL_COM1_BASE);
        serial_configure_modem(SERIAL_COM1_BASE);
        serial_configured = 1;
    }

    while(!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE)) {
        ;
    }

    unsigned int i = 0;
    while(buf[i] != '\0') {
        serial_write_cell(SERIAL_COM1_BASE, buf[i]);
        i++;
    }
}

#endif
