AS=i686-elf-gcc -m32 -c -g -mgeneral-regs-only -mno-red-zone
CC=i686-elf-gcc -m32 -g -mgeneral-regs-only -mno-red-zone
LD=i686-elf-gcc -m32

build: kernel.bin

boot.o: boot.s
	$(AS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

interrupts.o: ./kernel/interrupts/interrupts.c
	$(CC) -c ./kernel/interrupts/interrupts.c -o interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include -I./libc/include

vga_entry.o: ./kernel/vga/vga_entry.c
	$(CC) -c ./kernel/vga/vga_entry.c -o vga_entry.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include

vga_entry_color.o: ./kernel/vga/vga_entry_color.c
	$(CC) -c ./kernel/vga/vga_entry_color.c -o vga_entry_color.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include

memcmp.o: ./libc/string/memcmp.c
	$(CC) -c ./libc/string/memcmp.c -o memcmp.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

memchr.o: ./libc/string/memchr.c
	$(CC) -c ./libc/string/memchr.c -o memchr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

memcpy.o: ./libc/string/memcpy.c
	$(CC) -c ./libc/string/memcpy.c -o memcpy.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

memset.o: ./libc/string/memset.c
	$(CC) -c ./libc/string/memset.c -o memset.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

strchr.o: ./libc/string/strchr.c
	$(CC) -c ./libc/string/strchr.c -o strchr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

strcmp.o: ./libc/string/strcmp.c
	$(CC) -c ./libc/string/strcmp.c -o strcmp.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

strlen.o: ./libc/string/strlen.c
	$(CC) -c ./libc/string/strlen.c -o strlen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include

tty.o: ./kernel/tty/tty.c
	$(CC) -c ./kernel/tty/tty.c -o tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

vprintf.o: ./libc/stdio/vprintf.c
	$(CC) -c ./libc/stdio/vprintf.c -o vprintf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

printf.o: ./libc/stdio/printf.c
	$(CC) -c ./libc/stdio/printf.c -o printf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

panic_maker.o: ./kernel/panic/panic_maker.c
	$(CC) -c ./kernel/panic/panic_maker.c -o panic_maker.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

halt_but_dont_catch_fire.o: ./kernel/panic/halt_but_dont_catch_fire.c
	$(CC) -c ./kernel/panic/halt_but_dont_catch_fire.c -o halt_but_dont_catch_fire.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

validate_acpi.o: ./kernel/acpi/validate_acpi.c
	$(CC) -c ./kernel/acpi/validate_acpi.c -o validate_acpi.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

get_rsdp_descriptor.o: ./kernel/acpi/get_rsdp_descriptor.c
	$(CC) -c ./kernel/acpi/get_rsdp_descriptor.c -o get_rsdp_descriptor.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

apic.o: ./kernel/apic/apic.c
	$(CC) -c ./kernel/apic/apic.c -o apic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include -I./libc/include

get_contiguous_memory_size.o: ./kernel/memory_map/get_contiguous_memory_size.c
	$(CC) -c ./kernel/memory_map/get_contiguous_memory_size.c -o get_contiguous_memory_size.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

display_memory_size.o: ./kernel/memory_map/display_memory_size.c
	$(CC) -c ./kernel/memory_map/display_memory_size.c -o display_memory_size.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

display_memory_map.o: ./kernel/memory_map/display_memory_map.c
	$(CC) -c ./kernel/memory_map/display_memory_map.c -o display_memory_map.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

get_next_mmap_entry.o: ./kernel/memory_map/get_next_mmap_entry.c
	$(CC) -c ./kernel/memory_map/get_next_mmap_entry.c -o get_next_mmap_entry.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

kernel.bin: kernel.o boot.o vga_entry.o vga_entry_color.o interrupts.o memchr.o memcpy.o memset.o strchr.o strcmp.o strlen.o printf.o vprintf.o tty.o panic_maker.o halt_but_dont_catch_fire.o get_contiguous_memory_size.o display_memory_size.o get_next_mmap_entry.o display_memory_map.o get_rsdp_descriptor.o validate_acpi.o apic.o
	$(LD) -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib vga_entry.o vga_entry_color.o boot.o interrupts.o  memchr.o memcpy.o memset.o strchr.o strcmp.o strlen.o kernel.o printf.o vprintf.o tty.o panic_maker.o halt_but_dont_catch_fire.o get_contiguous_memory_size.o display_memory_size.o get_next_mmap_entry.o display_memory_map.o get_rsdp_descriptor.o validate_acpi.o apic.o -lgcc

.PHONY: build

clean:
	rm *.o
