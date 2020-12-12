#pragma once


struct iframe {
    int ip;
    int cs;
    int flags;
    int sp;
    int ss;
};

void init_idt();

void timer_phase(int hz);

void hard_sleep(uint64_t seconds);
