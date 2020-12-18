#include "stdio.h"

int printf(const char* format_string, ...) {
	va_list arg_list;
	va_start(arg_list, format_string);

	vprintf(format_string, arg_list);

	va_end(arg_list);
}
