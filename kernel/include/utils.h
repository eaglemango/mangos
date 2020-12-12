#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t data) {
  asm volatile("out %0, %1" : : "a" (data), "d" (port));
}

static inline uint8_t inb(uint16_t port) {
  asm volatile("in %0, %%al" : : "d" (port));
}

#endif
