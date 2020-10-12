#include "string.h"

void* memchr(const void* ptr, int symbol, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (((char*) ptr)[i] == (char) symbol) {
            return ((char*) ptr) + i; 
        }
    }

    return NULL;
}
