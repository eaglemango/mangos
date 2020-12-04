#pragma once

#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "string.h"

void terminal_initialize(void);

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

void terminal_scroll();

void terminal_putchar_color(char c, uint8_t color);

void terminal_write(const char* data, size_t size, uint8_t color);

void terminal_writestring(const char* data);

void terminal_writestring_color(const char* data, uint8_t color);

#endif
