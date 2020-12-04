#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stddef.h>

#include "tty.h"

int vprintf(const char* format_string, va_list arg_list);
int printf(const char* format_string, ...);

#endif
