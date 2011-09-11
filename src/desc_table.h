
#ifndef __DESC_TABLE__
#define __DESC_TABLE__

#include "common.h"

typedef struct gdt_entry
{
	u16	limit_low;			// the lower 16 bits of the limit.
	u16	base_low;			// the lower 16 bits of the base.
	u8	base_middle;		// the next 8 bits of the base.
	u8	access;				// access flags, determine what ring
							// this segment can be used in.
	u8	granularity;
	u8	base_high;			// the last 8 bits of the base.
}
__attribute__((packed))
gdt_entry_t;

typedef struct gdt_ptr
{
	u16	limit;
	u32	base;			// The address of the first element
						// in our gdt_entry_t array.
}
__attribute__((packed))
gdt_ptr_t;

typedef struct idt_entry
{
	// The lower 16 bits of the address to jump to
	// when this interrupt fires.
	u16	base_lo;
	u16	sel;			// Kernel segment selector.
	u8	always0;		// This must always be zero.
	u8	flags;			// More flags. See documentation.
	u16	base_hi;		// The upper 16 bits of the address to jump to.
}
__attribute__((packed))	// it have to be packed.
idt_entry_t;

typedef struct idt_ptr
{
	u16	limit;
	u32	base;			// The address of the first element
						// in our idt_entry_t array.
}
__attribute__((packed))
idt_ptr_t;

void init_idt(void);
void init_gdt(void);

#endif

