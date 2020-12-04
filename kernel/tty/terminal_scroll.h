#ifndef TERMINAL_SCROLL_H
#define TERMINAL_SCROLL_H

void terminal_scroll() {
	for (size_t i = 1; i < VGA_HEIGHT; ++i) {
		memcpy(&terminal_buffer[VGA_WIDTH * (i - 1)], &terminal_buffer[VGA_WIDTH * i], VGA_WIDTH * 2);
	}

	memset(&terminal_buffer[VGA_WIDTH * (VGA_HEIGHT - 1)], 0, VGA_WIDTH * 2);
}

#endif
