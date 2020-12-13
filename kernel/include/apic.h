#ifndef APIC_H
#define APIC_H

#include "acpi.h"
#include "utils.h"
#include "interrupts.h"

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

madt_t* get_madt(rsdt_t* rsdt);

struct ioapic {
    uint32_t reg;
    uint32_t pad[3];
    uint32_t data;
};
typedef struct ioapic ioapic_t;

#define APIC_ID          0x20
#define APIC_VER         0x30
#define APIC_TASKPRIOR   0x80
#define APIC_EOI         0x0B0
#define APIC_LDR         0x0D0
#define APIC_DFR         0x0E0
#define APIC_SPURIOUS    0x0F0
#define APIC_ESR         0x280
#define APIC_ICRL        0x300
#define APIC_ICRH        0x310
#define APIC_LVT_TMR     0x320
#define APIC_LVT_PERF    0x340
#define APIC_LVT_LINT0   0x350
#define APIC_LVT_LINT1   0x360
#define APIC_LVT_ERR     0x370
#define APIC_TMRINITCNT  0x380
#define APIC_TMRCURRCNT  0x390
#define APIC_TMRDIV      0x3E0
#define APIC_LAST        0x38F
#define APIC_DISABLE     0x10000
#define APIC_SW_ENABLE   0x100
#define APIC_CPUFOCUS    0x200
#define APIC_NMI         (4<<8)
#define APIC_INIT        0x500
#define APIC_BCAST       0x80000
#define APIC_LEVEL       0x8000
#define APIC_DELIVS      0x1000
#define TMR_PERIODIC     0x20000
#define TMR_BASEDIV      (1<<20)

static void lapic_write(uint32_t* lapic_ptr, size_t idx, uint32_t value);

static uint32_t lapic_read(uint32_t* lapic_ptr, size_t idx);

uint32_t get_apic_timer_ticks(uint32_t* lapic_ptr);

void init_apic(rsdt_t* rsdt);

void apic_eoi();

#define IOAPIC_REG_TABLE  0x10

static void ioapic_write(int reg, uint32_t data);

static void ioapic_enable(int irq, int target_irq);

#endif
