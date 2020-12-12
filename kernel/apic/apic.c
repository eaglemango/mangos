#include "apic.h"

madt_t* get_madt(rsdt_t* rsdt) {
    int entries_count = (rsdt->header.length - sizeof(rsdt->header)) / 4;

    // printf("RSDT entries count: %d\n", entries_count);

    for (int i = 0; i < entries_count; ++i) {
        acpi_sdt_header_t* curr_header = (acpi_sdt_header_t*) rsdt->pointer_to_other_sdt[i];

        if (!memcmp(curr_header->signature, MADT_MAGIC, strlen(MADT_MAGIC))) {
            return (madt_t*) curr_header;
        }
    }

    PANIC("MADT wasn't found")

    return NULL;
}

static void lapic_write(uint32_t* lapic_ptr, size_t idx, uint32_t value) {
    lapic_ptr[idx / 4] = value;
    lapic_ptr[0];
}

static uint32_t lapic_read(uint32_t* lapic_ptr, size_t idx) {
    return lapic_ptr[idx / 4];
}

uint32_t get_apic_timer_ticks(uint32_t* lapic_ptr) {
        // Tell APIC timer to use divider 16
        lapic_write(lapic_ptr, APIC_TMRDIV, 0x3);
 
        // Set APIC init counter to -1
        lapic_write(lapic_ptr, APIC_TMRINITCNT, 0xFFFFFFFF);
 
        // Perform PIT-supported sleep for 10sec
        hard_sleep(10);
 
        // Now we know how often the APIC timer has ticked in 10s
        uint32_t ticksIn10s = 0xFFFFFFFF - lapic_read(lapic_ptr, APIC_TMRCURRCNT);

        uint32_t ticksIn1ms = ticksIn10s / 10000;

        return ticksIn1ms;
}

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

    uint32_t ticksIn1ms = get_apic_timer_ticks(lapic_ptr);

    // Disable old PIC.
    outb(0x20 + 1, 0xFF);
    outb(0xA0 + 1, 0xFF);

    lapic_write(lapic_ptr, APIC_SPURIOUS, 39 | APIC_SW_ENABLE);

    lapic_write(lapic_ptr, APIC_LVT_PERF, APIC_DISABLE);
    lapic_write(lapic_ptr, APIC_LVT_LINT0, APIC_DISABLE);
    lapic_write(lapic_ptr, APIC_LVT_LINT1, APIC_DISABLE);

    lapic_write(lapic_ptr, APIC_EOI, 0);

    lapic_write(lapic_ptr, APIC_TASKPRIOR, 0);

    // Start timer as periodic on IRQ 0, divider 16, with the number of ticks we counted
    change_timer_type(APIC_TIMER);
    change_tps(1000);
    lapic_write(lapic_ptr, APIC_LVT_TMR, 32 | TMR_PERIODIC);
    lapic_write(lapic_ptr, APIC_TMRDIV, 0x3);
    lapic_write(lapic_ptr, APIC_TMRINITCNT, ticksIn1ms);
}

void apic_eoi() {
    madt_t* madt = get_madt((rsdt_t *) get_rsdp_descriptor()->rsdt_addr);

    uint32_t* lapic_ptr = (uint32_t*) madt->lapic_addr;

    lapic_write(lapic_ptr, APIC_EOI, 0);
}
