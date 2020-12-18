#include "string.h"

int memcmp(const void* mem_1, const void* mem_2, size_t size) {
    size_t i = 0;
    while (i < size) {
        if (((char*) mem_1)[i] > ((char*) mem_2)[i]) {
            return 1;
        }

        if (((char*) mem_1)[i] < ((char*) mem_2)[i]) {
            return -1;
        }

        ++i;
    }

    return 0;
}