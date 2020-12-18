#include "memory_map.h"

contiguous_memory_size_t get_contiguous_memory_size(multiboot_info_t* multiboot_info) {
    contiguous_memory_size_t memory_size = { .mem_lower = 0, .mem_upper = 0 };

    memory_size.mem_lower = multiboot_info->mem_lower;
    memory_size.mem_upper = multiboot_info->mem_upper;

    return memory_size;
}
