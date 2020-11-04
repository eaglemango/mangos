#include "string.h"

char* strchr(const char* str, int symbol) {
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == (char) symbol) {
            return ((char*) str) + i;
        }
        
        ++i;
    }

    return NULL;
}
