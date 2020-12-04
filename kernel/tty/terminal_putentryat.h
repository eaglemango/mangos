#ifndef TERMINAL_PUTENTRYAT_H
#define TERMINAL_PUTENTRYAT_H

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

#endif
