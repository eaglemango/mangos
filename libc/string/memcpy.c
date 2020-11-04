#include "string.h"

void* memcpy(void* dest_ptr, const void* src_ptr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        ((char*) dest_ptr)[i] = ((char*) src_ptr)[i];
    }

    return dest_ptr;
}
