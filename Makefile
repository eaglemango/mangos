AS=i686-elf-gcc -m32 -c -g -mgeneral-regs-only -mno-red-zone
CC=i686-elf-gcc -m32 -g -mgeneral-regs-only -mno-red-zone
LD=i686-elf-gcc -m32

build: kernel.bin

boot.o: boot.s
	$(AS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

interrupts.o: interrupts.c
	$(CC) -c interrupts.c -o interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

vga_entry.o: ./kernel/vga/vga_entry.c
	$(CC) -c ./kernel/vga/vga_entry.c -o vga_entry.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include

vga_entry_color.o: ./kernel/vga/vga_entry_color.c
	$(CC) -c ./kernel/vga/vga_entry_color.c -o vga_entry_color.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./kernel/include

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

printf.o: ./libc/stdio/printf.c
	$(CC) -c ./libc/stdio/printf.c -o printf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./libc/include -I./kernel/include

kernel.bin: kernel.o boot.o vga_entry.o vga_entry_color.o interrupts.o memchr.o memcpy.o memset.o strchr.o strcmp.o strlen.o printf.o tty.o
	$(LD) -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib vga_entry.o vga_entry_color.o boot.o interrupts.o  memchr.o memcpy.o memset.o strchr.o strcmp.o strlen.o kernel.o printf.o tty.o -lgcc

.PHONY: build

clean:
	rm *.o
