#include "panic.h"

void halt_but_dont_catch_fire() {
    asm volatile ("cli");

    while (1) {
        asm volatile ("hlt");
    }
}
