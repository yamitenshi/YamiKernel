#include "inc/driver.h"
#include "inc/colors.h"

void kmain() {
	clearScreen((color){ .fg = FB_LGREY, .bg = FB_BLACK });

	write("Scrolling terminal test...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLower end of screen....\n\n\n\n\n\nThis should be scrolled now", (color){ .fg = FB_LGREY, .bg = FB_BLACK});
	return;
}
