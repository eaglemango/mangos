#include "acpi.h"

void validate_acpi(rsdp_descriptor_t* rsdp_descriptor_) {
    // Check if ACPI version is supported (only 1.0 is supported for now)
    if (rsdp_descriptor_->revision != 0) {
        PANIC("unsupported ACPI version: %d", rsdp_descriptor_->revision)
    }

    // Checksum validation ====================================================
    uint32_t sum = 0;
    for (size_t i = 0; i < sizeof(*rsdp_descriptor_); ++i) {
        sum += ((uint8_t*) rsdp_descriptor_)[i];
    }
    
    // Lower byte of sum must be equal to zero
    if ((sum & 0xFF) != 0) {
        PANIC("ACPI table checksum is invalid: %d", sum)
    }
    // ========================================================================
}
