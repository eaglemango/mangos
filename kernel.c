#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "interrupts.h"
#include "stdio.h"
#include "tty.h"
#include "vga.h"

__attribute__ ((interrupt)) void isr0(struct iframe* frame) {
    terminal_writestring_color("Hello world!\n", vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    (void)frame;
}

void kernel_main(void) {
    init_idt();

	terminal_initialize();
    asm volatile ("sti");
    asm volatile ("int $0x80");

    terminal_writestring_color("(c) eaglemango", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));

    printf("\nhello!");
}
