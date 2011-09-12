
#include "desc_table.h"

// in desc_table_flush.s
extern void idt_flush(idt_ptr_t * p);
extern void gdt_flush(gdt_ptr_t * p);

// in interrupt.s
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

static void gdt_set_gate(s32 num, u32 base, u32 limit, u8 access, u8 gran);
static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

idt_entry_t	idt_entries[256];
idt_ptr_t	idt_ptr;

void init_gdt(void)
{
	// set up gdt
	gdt_ptr.limit = sizeof(gdt_entry_t) * 5 - 1;
	gdt_ptr.base  = (u32)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdt_flush(&gdt_ptr);
}

void init_idt(void)
{
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base  = (u32)&idt_entries;

#define ISR(I)	idt_set_gate(I, (u32)&isr ## I, 0x08, 0x8E);
	ISR(0);
	ISR(1);
	ISR(2);
	ISR(3);
	ISR(4);
	ISR(5);
	ISR(6);
	ISR(7);
	ISR(8);
	ISR(9);
	ISR(10);
	ISR(11);
	ISR(12);
	ISR(13);
	ISR(14);
	ISR(15);
	ISR(16);
	ISR(17);
	ISR(18);
	ISR(19);
	ISR(20);
	ISR(21);
	ISR(22);
	ISR(23);
	ISR(24);
	ISR(25);
	ISR(26);
	ISR(27);
	ISR(28);
	ISR(29);
	ISR(30);
	ISR(31);
#undef ISR

	// Remap the irq table.
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

#define IRQ(I)	idt_set_gate(32 + I, (u32)&irq ## I, 0x08, 0x8E);
	IRQ(0);
	IRQ(1);
	IRQ(2);
	IRQ(3);
	IRQ(4);
	IRQ(5);
	IRQ(6);
	IRQ(7);
	IRQ(8);
	IRQ(9);
	IRQ(10);
	IRQ(11);
	IRQ(12);
	IRQ(13);
	IRQ(14);
	IRQ(15);
#undef IRQ

	idt_flush(&idt_ptr);
}

void gdt_set_gate(s32 num, u32 base, u32 limit, u8 access, u8 gran)
{
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}

void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;
	// must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	idt_entries[num].flags   = flags /* | 0x60 */;
}

