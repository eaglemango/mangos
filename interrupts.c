#include <stddef.h>
#include <stdint.h>

#include "panic.h"
#include "interrupts.h"

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry IDT[256];
struct idt_ptr IDTPTR;

static void idt_register(uint8_t pos, uint32_t base, uint16_t sel, uint8_t flags)
{
    IDT[pos].base_lo = base & 0xFFFF;
    IDT[pos].base_hi = (base >> 16) & 0xFFFF;

    IDT[pos].sel = sel;
    IDT[pos].zero = 0;
    IDT[pos].flags = flags;
}

extern void isr0();

static inline void outb(uint16_t port, uint8_t data) {
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline uint8_t inb(uint16_t port) {
  asm volatile("in %0, %%al" : : "d" (port));
}

static uint64_t ticks = 0;

static const uint64_t TICKS_PER_SECOND = 18;

__attribute__ ((interrupt)) void irq0(struct iframe* frame) {
    /*
    if (ticks % TICKS_PER_SECOND == 0) {
        printf("%d sec passed\n", ticks / TICKS_PER_SECOND);
    }
    */

    ++ticks;

    // PIC EOI
    outb(0x20, 0x20);

    (void)frame;
}

void hard_sleep(uint64_t seconds) {
    uint64_t wake_up_time = ticks + seconds * TICKS_PER_SECOND;

    while (ticks < wake_up_time) {
        asm volatile ("hlt");
    }
}

void init_idt() {
    IDTPTR.limit = sizeof(struct idt_entry) * 256 - 1;
    IDTPTR.base = (uint32_t)&IDT;

    /* remapping the PIC */
	outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // For flags param see https://wiki.osdev.org/IDT#Structure_IA-32.
    idt_register(32, (uint32_t)irq0, 0x08, 0b10001110);
    idt_register(0x80, (uint32_t)isr0, 0x08, 0b10001110);

    asm volatile (
        "lidt (%0)\n"
        :
        : "r"(&IDTPTR)
        :
    );
}
