#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

    terminal_writestring_color("(c) eaglemango", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));

    display_memory_size(multiboot_info);
    display_memory_map(multiboot_info);

    // PANIC("mangOS is not ready yet!")

    // printf("This message will never be printed because of panic!");
}
