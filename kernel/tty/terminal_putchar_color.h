#ifndef TERMINAL_PUTCHAR_COLOR_H
#define TERMINAL_PUTCHAR_COLOR_H

void terminal_putchar_color(char c, uint8_t color) {
    switch (c) {
    case '\n':
        ++terminal_row;
        terminal_column = 0;
        if (terminal_row == VGA_HEIGHT) {
            terminal_row = VGA_HEIGHT - 1;
			terminal_scroll();
        }
        break;

    default:
        terminal_putentryat(c, color, terminal_column, terminal_row);
        ++terminal_column;
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            ++terminal_row;
            if (terminal_row == VGA_HEIGHT) {
                terminal_row = VGA_HEIGHT - 1;
				terminal_scroll();
            }
        }
    }
}

#endif
