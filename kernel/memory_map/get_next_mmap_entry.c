#include "memory_map.h"

multiboot_memory_map_t* get_next_mmap_entry(multiboot_memory_map_t* mmap_entry) {
    return (multiboot_memory_map_t*)((uint32_t)mmap_entry + mmap_entry->size + sizeof(mmap_entry->size));
}
