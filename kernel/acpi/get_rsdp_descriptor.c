#include "acpi.h"

rsdp_descriptor_t* get_rsdp_descriptor() {
    // RSDP is somewhere between RSDP_SEARCH_BEGIN and RSDP_SEARCH_END
    char* curr_ptr = (char*) RSDP_SEARCH_BEGIN;
    while (curr_ptr < (char*) RSDP_SEARCH_END) {
        if (!memcmp(curr_ptr, RSDP_MAGIC, strlen(RSDP_MAGIC))) {
            rsdp_descriptor_t* rsdp_descriptor_ = (rsdp_descriptor_t*) curr_ptr;

            // 2-step validation: version support and checksum validation
            validate_acpi(rsdp_descriptor_);

            return rsdp_descriptor_;
        }

        // RSDP signature is aligned by 16 bytes
        curr_ptr += 16;
    }

    PANIC("RSDP descriptor wasn't found")

    return NULL;
}
