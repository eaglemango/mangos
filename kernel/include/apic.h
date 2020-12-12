#ifndef APIC_H
#define APIC_H

#include "acpi.h"

struct madt_entry {
    uint8_t entry_type;
    uint8_t record_length;
    uint8_t data[];
} __attribute__ ((packed));
typedef struct madt_entry madt_entry_t;

enum MADT_ENTRY_TYPE {
    PROCESSOR_LOCAL_APIC = 0,
    IO_APIC = 1,
    INTERRUPT_SOURCE_OVERRIDE = 2,
    NON_MASKABLE_INTERRUPTS = 4,
    LOCAL_APIC_ADDRESS_OVERRIDE = 5
};

// Multiple APIC Description Table
struct madt {
    acpi_sdt_header_t header;
    uint32_t lapic_addr;
    uint32_t flags;
    madt_entry_t first_entry;
} __attribute__ ((packed));
typedef struct madt madt_t;

// MADT signature
static const char MADT_MAGIC[] = "APIC";

madt_t* get_madt(rsdt_t* rsdt) {
    int entries_count = (rsdt->header.length - sizeof(rsdt->header)) / 4;

    printf("RSDT entries count: %d\n", entries_count);

    for (int i = 0; i < entries_count; ++i) {
        acpi_sdt_header_t* curr_header = (acpi_sdt_header_t*) rsdt->pointer_to_other_sdt[i];

        if (!memcmp(curr_header->signature, MADT_MAGIC, strlen(MADT_MAGIC))) {
            return (madt_t*) curr_header;
        }
    }

    PANIC("MADT wasn't found")

    return NULL;
}

struct ioapic {
    uint32_t reg;
    uint32_t pad[3];
    uint32_t data;
};
typedef struct ioapic ioapic_t;

void init_apic(rsdt_t* rsdt) {
    madt_t* madt = get_madt(rsdt);

    uint32_t* lapic_ptr = (uint32_t*) madt->lapic_addr;
    ioapic_t* ioapic_ptr = NULL;

    madt_entry_t* madt_entry = &madt->first_entry;
    while (madt_entry) {
        switch (madt_entry->entry_type) {
            case PROCESSOR_LOCAL_APIC:
                break;
            case IO_APIC:
                ioapic_ptr = (ioapic_t*)(*(uint32_t*)(&madt_entry->data[2]));
                break;
            case INTERRUPT_SOURCE_OVERRIDE:
                break;
            case NON_MASKABLE_INTERRUPTS:
                break;
            case LOCAL_APIC_ADDRESS_OVERRIDE:
                break;
            default:
                break;
        }

        madt_entry = (madt_entry_t*) ((uint8_t*) madt_entry + madt_entry->record_length);

        if ((uint8_t*) madt_entry >= (uint8_t*) madt + madt->header.length) {
            madt_entry = NULL;
        }
    }

    /*
    // Disable old PIC.
    outb(0x20 + 1, 0xFF);
    outb(0xA0 + 1, 0xFF);
    */
}

#endif
