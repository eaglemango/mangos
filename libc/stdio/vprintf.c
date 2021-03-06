#include "stdio.h"

int vprintf(const char* format_string, va_list arg_list) {
    char* curr_ptr = (char*) format_string;

	while (1) {
		char* next_modifier = strchr(curr_ptr, '%');

		if (next_modifier != NULL) {
			terminal_write(curr_ptr, next_modifier - curr_ptr, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

			if (next_modifier[1] == 'd') {
				int number = va_arg(arg_list, int);

				if (number < 0) {
					terminal_putchar_color('-', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
					number *= -1;
				}

				size_t i = 0;
				int str_number[10];
				if (number == 0) {
					str_number[0] = 0;
					i = 1;
				}
		
				while (number != 0) {
					str_number[i] = number % 10;
					number /= 10;
					++i;
				}
				
				while (i >= 1) {
					terminal_putchar_color('0' + str_number[i - 1], vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
					--i;
				}

				curr_ptr = next_modifier + 2;
			} else if (next_modifier[1] == 'x') {
				unsigned int number = va_arg(arg_list, unsigned int);

				size_t i = 0;
				int str_number[10];
				if (number == 0) {
					str_number[0] = 0;
					i = 1;
				}
		
				while (number != 0) {
					str_number[i] = number % 16;
					number /= 16;
					++i;
				}
				
				while (i >= 1) {
					if (str_number[i - 1] < 10) {
						terminal_putchar_color('0' + str_number[i - 1], vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
						--i;
					} else {
						terminal_putchar_color('a' + str_number[i - 1] - 10, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
						--i;
					}
				}

				curr_ptr = next_modifier + 2;
			} else if (next_modifier[1] == 'x' || next_modifier[1] == 'X') {
				unsigned int number = va_arg(arg_list, unsigned int);

				size_t i = 0;
				int str_number[10];
				if (number == 0) {
					str_number[0] = 0;
					i = 1;
				}
		
				while (number != 0) {
					str_number[i] = number % 16;
					number /= 16;
					++i;
				}

				char hex_ten = 'a';
				if (next_modifier[1] == 'X') {
					hex_ten = 'A';
				}
				
				while (i >= 1) {
					if (str_number[i - 1] < 10) {
						terminal_putchar_color('0' + str_number[i - 1], vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
						--i;
					} else {
						terminal_putchar_color(hex_ten + str_number[i - 1] - 10, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
						--i;
					}
				}

				curr_ptr = next_modifier + 2;
			} else if (next_modifier[1] == 'u') {
				unsigned int number = va_arg(arg_list, unsigned int);

				size_t i = 0;
				int str_number[10];
				if (number == 0) {
					str_number[0] = 0;
					i = 1;
				}
		
				while (number != 0) {
					str_number[i] = number % 10;
					number /= 10;
					++i;
				}
				
				while (i >= 1) {
					terminal_putchar_color('0' + str_number[i - 1], vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
					--i;
				}

				curr_ptr = next_modifier + 2;
			} else if (next_modifier[1] == 's') {
				char* string = va_arg(arg_list, char*);

				terminal_writestring(string);

				curr_ptr = next_modifier + 2;
			} else if (next_modifier[1] == '%') {
				terminal_putchar_color('%', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

				curr_ptr = next_modifier + 2;				
			} else {
				terminal_putchar_color('%', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

				curr_ptr = next_modifier + 1;
			}
		} else {
			terminal_writestring(curr_ptr);

			break;
		}
	}
}
