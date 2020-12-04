#ifndef TERMINAL_WRITESTRING_COLOR_H
#define TERMINAL_WRITESTRING_COLOR_H

void terminal_writestring_color(const char* data, uint8_t color) {
    terminal_write(data, strlen(data), color);
}

#endif
