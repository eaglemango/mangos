#include "string.h"

int strcmp(const char* str_1, const char* str_2) {
    size_t i = 0;
    while (str_1[i] != '\0' || str_2[i] != '\0') {
        if (str_1[i] > str_2[i]) {
            return 1;
        }

        if (str_1[i] < str_2[i]) {
            return -1;
        }

        ++i;
    }

    return 0;
}
