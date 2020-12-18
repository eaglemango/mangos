#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "acpi.h"
#include "apic.h"
#include "interrupts.h"
#include "memory_map.h"
#include "multiboot.h"
#include "panic.h"
#include "stdio.h"
#include "tty.h"
#include "vga.h"

__attribute__ ((interrupt)) void isr0(struct iframe* frame) {
    terminal_writestring_color("Hello world!\n", vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    (void)frame;
}

void kernel_main(multiboot_info_t* multiboot_info, unsigned int magic) {
    init_idt();

	terminal_initialize();
    asm volatile ("sti");
    asm volatile ("int $0x80");

    printf("Using PIT...\n");

    terminal_writestring_color("(c) eaglemango", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));

    rsdp_descriptor_t* rsdp = get_rsdp_descriptor();
    madt_t* madt = get_madt(rsdp->rsdt_addr);
    init_apic(rsdp->rsdt_addr);
    printf("Using APIC timer...\n");
}
