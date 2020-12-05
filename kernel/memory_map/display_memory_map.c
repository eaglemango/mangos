#include "memory_map.h"

void display_memory_map(multiboot_info_t* multiboot_info) {
    // Check if bit 6 is set
    if (multiboot_info->flags & MULTIBOOT_INFO_MEM_MAP) {
        // Message header
        printf("================================== MEMORY MAP ==================================\n");

        // Print mmap table info
        printf("Table info: mmap_addr = 0x%X | mmap_length = %u\n\n",
                multiboot_info->mmap_addr,
                multiboot_info->mmap_length);

        // Print all mmap table entries
        multiboot_memory_map_t* curr_entry = (multiboot_memory_map_t*)multiboot_info->mmap_addr;
        while ((uint32_t)curr_entry < multiboot_info->mmap_addr + multiboot_info->mmap_length) {
            printf("Entry found: base_addr_low = 0x%X | base_addr_high = 0x%X | "
                    "length_low = 0x%X | length_high = 0x%X | type = 0x%X\n\n",
                    curr_entry->base_addr_low,
                    curr_entry->base_addr_high,
                    curr_entry->length_low,
                    curr_entry->length_high,
                    curr_entry->type);

            curr_entry = get_next_mmap_entry(curr_entry);
        }
        
        // Message footer
        printf("================================================================================");
    } else {
        PANIC("MULTIBOOT_INFO_MEM_MAP is not set")
    }
}
