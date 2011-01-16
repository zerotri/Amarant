#include <machine/x86/gdt.h>
#include <machine/x86/pio.h>
#include <memory.h>
extern "C" void kernel_gdt_flush(uint32_t);
extern "C" void kernel_idt_flush(uint32_t);
GDT::entry_t GDT::m_entries[5];
GDT::ptr_t   GDT::m_ptr;
IDT::entry_t IDT::m_entries[256];
IDT::ptr_t   IDT::m_ptr;

void GDT::initialize()
{
	m_ptr.limit = (sizeof(GDT::entry_t) * 5) - 1;
    m_ptr.base  = (uint32_t)&GDT::m_entries;

    setGate(0, 0, 0, 0, 0);                // Null segment
    setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    flush((uint32_t)&m_ptr);
}
void GDT::flush(uint32_t ptr)
{
	kernel_gdt_flush(ptr);
}
void GDT::setGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	m_entries[num].base_low    = (base & 0xFFFF);
    m_entries[num].base_middle = (base >> 16) & 0xFF;
    m_entries[num].base_high   = (base >> 24) & 0xFF;

    m_entries[num].limit_low   = (limit & 0xFFFF);
    m_entries[num].granularity = (limit >> 16) & 0x0F;
    
    m_entries[num].granularity |= gran & 0xF0;
    m_entries[num].access      = access;
}

void IDT::initialize()
{
	m_ptr.limit = sizeof(IDT::entry_t) * 256 -1;
    m_ptr.base  = (uint32_t)&IDT::m_entries;

    memset((uint8_t*)&m_entries, 0, sizeof(IDT::entry_t)*256);

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

    setGate( 0, (uint32_t)isr0 , 0x08, 0x8E);
    setGate( 1, (uint32_t)isr1 , 0x08, 0x8E);
    setGate( 2, (uint32_t)isr2 , 0x08, 0x8E);
    setGate( 3, (uint32_t)isr3 , 0x08, 0x8E);
    setGate( 4, (uint32_t)isr4 , 0x08, 0x8E);
    setGate( 5, (uint32_t)isr5 , 0x08, 0x8E);
    setGate( 6, (uint32_t)isr6 , 0x08, 0x8E);
    setGate( 7, (uint32_t)isr7 , 0x08, 0x8E);
    setGate( 8, (uint32_t)isr8 , 0x08, 0x8E);
    setGate( 9, (uint32_t)isr9 , 0x08, 0x8E);
    setGate(10, (uint32_t)isr10, 0x08, 0x8E);
    setGate(11, (uint32_t)isr11, 0x08, 0x8E);
    setGate(12, (uint32_t)isr12, 0x08, 0x8E);
    setGate(13, (uint32_t)isr13, 0x08, 0x8E);
    setGate(14, (uint32_t)isr14, 0x08, 0x8E);
    setGate(15, (uint32_t)isr15, 0x08, 0x8E);
    setGate(16, (uint32_t)isr16, 0x08, 0x8E);
    setGate(17, (uint32_t)isr17, 0x08, 0x8E);
    setGate(18, (uint32_t)isr18, 0x08, 0x8E);
    setGate(19, (uint32_t)isr19, 0x08, 0x8E);
    setGate(20, (uint32_t)isr20, 0x08, 0x8E);
    setGate(21, (uint32_t)isr21, 0x08, 0x8E);
    setGate(22, (uint32_t)isr22, 0x08, 0x8E);
    setGate(23, (uint32_t)isr23, 0x08, 0x8E);
    setGate(24, (uint32_t)isr24, 0x08, 0x8E);
    setGate(25, (uint32_t)isr25, 0x08, 0x8E);
    setGate(26, (uint32_t)isr26, 0x08, 0x8E);
    setGate(27, (uint32_t)isr27, 0x08, 0x8E);
    setGate(28, (uint32_t)isr28, 0x08, 0x8E);
    setGate(29, (uint32_t)isr29, 0x08, 0x8E);
    setGate(30, (uint32_t)isr30, 0x08, 0x8E);
    setGate(31, (uint32_t)isr31, 0x08, 0x8E);
    setGate(32, (uint32_t)irq0, 0x08, 0x8E);
    setGate(33, (uint32_t)irq1, 0x08, 0x8E);
    setGate(34, (uint32_t)irq2, 0x08, 0x8E);
    setGate(35, (uint32_t)irq3, 0x08, 0x8E);
    setGate(36, (uint32_t)irq4, 0x08, 0x8E);
    setGate(37, (uint32_t)irq5, 0x08, 0x8E);
    setGate(38, (uint32_t)irq6, 0x08, 0x8E);
    setGate(39, (uint32_t)irq7, 0x08, 0x8E);
    setGate(40, (uint32_t)irq8, 0x08, 0x8E);
    setGate(41, (uint32_t)irq9, 0x08, 0x8E);
    setGate(42, (uint32_t)irq10, 0x08, 0x8E);
    setGate(43, (uint32_t)irq11, 0x08, 0x8E);
    setGate(44, (uint32_t)irq12, 0x08, 0x8E);
    setGate(45, (uint32_t)irq13, 0x08, 0x8E);
    setGate(46, (uint32_t)irq14, 0x08, 0x8E);
    setGate(47, (uint32_t)irq15, 0x08, 0x8E);

    flush((uint32_t)&m_ptr);
}
void IDT::flush(uint32_t ptr)
{
	kernel_idt_flush(ptr);
}
void IDT::setGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	m_entries[num].base_lo = base & 0xFFFF;
    m_entries[num].base_hi = (base >> 16) & 0xFFFF;

    m_entries[num].sel     = sel;
    m_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    m_entries[num].flags   = flags /* | 0x60 */;
}