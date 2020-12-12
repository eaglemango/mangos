#include <stddef.h>
#include <stdint.h>

#include "panic.h"
#include "interrupts.h"
#include "utils.h"

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

static uint64_t ticks = 0;

static uint64_t timer_type = PIT_TIMER;

static const uint64_t DEFAULT_PIT_TPS = 18;
static uint64_t ticks_per_second = DEFAULT_PIT_TPS;

void change_timer_type(uint64_t new_type) {
    timer_type = new_type;
}

void change_tps(uint64_t new_tps) {
    ticks_per_second = new_tps;
}

__attribute__ ((interrupt)) void irq0(struct iframe* frame) {
    if (ticks % ticks_per_second == 0) {
        printf("%d sec passed\n", ticks / ticks_per_second);
    }

    ++ticks;

    if (timer_type == 0) {
        // PIC EOI
        outb(0x20, 0x20);
    } else if (timer_type == 1) {
        // APIC EOI
        apic_eoi();
    }

    (void)frame;
}

void hard_sleep(uint64_t seconds) {
    uint64_t wake_up_time = ticks + seconds * ticks_per_second;

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
