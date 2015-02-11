#include "inc/colors.h"
#include "inc/framebuffer.h"

void kmain() {
	const char *message = "Hello Kernel!";
	unsigned short i = 0;

	// Essentially clear the screen
	for(unsigned short x = 0; x < FB_WIDTH; x++) {
		for(unsigned short y = 0; y < FB_HEIGHT; y++) {
			unsigned int index = y*FB_WIDTH + x;
			fb_write_cell(index * 2, ' ', FB_LGREY, FB_BLACK);
		}
	}

	while(message[i] != '\0') {
		fb_write_cell(2 * i, message[i], FB_LGREY, FB_BLACK);
		i++;
	}

	return;
}
