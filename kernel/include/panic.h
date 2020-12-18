#ifndef PANIC_H
#define PANIC_H

#include <stdarg.h>

#include "stdio.h"

#define STR(x) #x
#define XSTR(x) STR(x)

void halt_but_dont_catch_fire();

void panic_maker(const char* when, const char* where, const char* why, ...);

#define PANIC(why, ...) panic_maker("at " __TIME__ " on " __DATE__, __FILE__ ":" XSTR(__LINE__), why __VA_OPT__(,) __VA_ARGS__);

#define PANIC_WHEN(condition) if (condition) PANIC("undesired condition reached (" #condition ")")
#define PANIC_WHEN_NULL(expression) PANIC_WHEN(expression == NULL)
#define PANIC_WHEN_NEGATIVE(expression) PANIC_WHEN(expression < 0)

#endif
