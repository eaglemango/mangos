#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void* memcpy(void* dest_ptr, const void* src_ptr, size_t size);
void* memset(void* ptr, int value, size_t size);
void* memchr(const void* ptr, int symbol, size_t size);

size_t strlen(const char* str);

#endif
