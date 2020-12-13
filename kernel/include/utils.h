#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t data) {
  asm volatile("out %0, %1" : : "a" (data), "d" (port));
}

static inline char inb(uint16_t port) {
  char data;

  asm volatile ("in %1,%0" : "=a" (data) : "d" (port));

  return data;
}

#endif
