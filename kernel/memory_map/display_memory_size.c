#include "memory_map.h"

void display_memory_size(multiboot_info_t* multiboot_info) {
    // Check if bit 0 is set
    if (multiboot_info->flags & MULTIBOOT_INFO_MEMORY) {
        contiguous_memory_size_t memory_size = get_contiguous_memory_size(multiboot_info);
        
        printf(
            "Memory size: mem_lower = %dKiB | mem_upper = %dKiB\n",
            memory_size.mem_lower,
            memory_size.mem_upper
        );
    } else {
        PANIC("MULTIBOOT_INFO_MEMORY is not set")
    }
}
