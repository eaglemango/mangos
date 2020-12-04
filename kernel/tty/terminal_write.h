#ifndef TERMINAL_WRITE_H
#define TERMINAL_WRITE_H

void terminal_write(const char* data, size_t size, uint8_t color) {
	for (size_t i = 0; i < size; ++i) {
        terminal_putchar_color(data[i], color);
    }
}

#endif
