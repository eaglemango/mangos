#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "apic.h"

struct iframe {
    int ip;
    int cs;
    int flags;
    int sp;
    int ss;
};

enum {
    PIT_TIMER = 0,
    APIC_TIMER = 1
};

void init_idt();

void timer_phase(int hz);

void hard_sleep(uint64_t seconds);

void change_timer_type(uint64_t new_type);

void change_tps(uint64_t new_tps);

#endif
