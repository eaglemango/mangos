#ifndef TERMINAL_WRITESTRING_H
#define TERMINAL_WRITESTRING_H

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data), vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
}

#endif
