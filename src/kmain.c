#include "inc/driver.h"
#include "inc/colors.h"

void kmain() {
	char clear_screen[80*25] = {0};
	write(clear_screen, 80*25, FB_LGREY, FB_BLACK);

	write("Booting YamiKernel...\n", 22, FB_LGREY, FB_BLACK);
	return;
}
