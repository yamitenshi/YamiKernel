#include "inc/driver.h"
#include "inc/colors.h"

void kmain() {
	clearScreen((color){ .fg = FB_WHITE, .bg = FB_BLUE });

	write("ERROR 0x1D107\n\nCould not find resource \"Intelligence\"\nSystem will now halt. Drink more coffee and try again.", (color){ .fg = FB_WHITE, .bg = FB_BLUE });
	return;
}
