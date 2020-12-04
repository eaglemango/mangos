#ifndef PANIC_H
#define PANIC_H

#include <stdarg.h>

#include "stdio.h"

#define STR(x) #x
#define XSTR(x) STR(x)

void halt_but_dont_catch_fire();

void panic_maker(const char* when, const char* where, const char* why, ...);

#define panic(why, ...) panic_maker("at " __TIME__ " on " __DATE__, __FILE__ ":" XSTR(__LINE__), why __VA_OPT__(,) __VA_ARGS__);

#endif
