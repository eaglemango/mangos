#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "panic.h"
#include "stdio.h"

struct contiguous_memory_size {
    multiboot_uint32_t mem_lower;
    multiboot_uint32_t mem_upper;
};
typedef struct contiguous_memory_size contiguous_memory_size_t;

contiguous_memory_size_t get_contiguous_memory_size(multiboot_info_t* multiboot_info);

multiboot_memory_map_t* get_next_mmap_entry(multiboot_memory_map_t* mmap_entry);

void display_memory_size(multiboot_info_t* multiboot_info);

void display_memory_map(multiboot_info_t* multiboot_info);

#endif
