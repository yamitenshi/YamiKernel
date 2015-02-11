#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#define FB_WIDTH    80
#define FB_HEIGHT   25

char *fb = (char*)0x000B8000;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4) | (fg & 0x0f);
}

#endif
