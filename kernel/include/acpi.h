#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>

#include "panic.h"
#include "string.h"

struct rsdp_descriptor {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_addr;
} __attribute__ ((packed));
typedef struct rsdp_descriptor rsdp_descriptor_t;

// System Description Table Header
struct acpi_sdt_header {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __attribute__ ((packed));
typedef struct acpi_sdt_header acpi_sdt_header_t;

// Root System Description Table
struct rsdt {
    acpi_sdt_header_t header;
    uint32_t pointer_to_other_sdt[];
} __attribute__ ((packed));
typedef struct rsdt rsdt_t;

// RSDP signature
static const char RSDP_MAGIC[] = "RSD PTR ";

// We can find RSDP only in that area
static const uint32_t RSDP_SEARCH_BEGIN = 0x000E0000;
static const uint32_t RSDP_SEARCH_END = 0x000FFFFF;

void validate_acpi(rsdp_descriptor_t* rsdp_descriptor_);

rsdp_descriptor_t* get_rsdp_descriptor();

#endif
