#ifndef GDT_H
#define GDT_H
#include <stdint.h>




class GDT
{
public:
	struct ptr_struct
	{
	   uint16_t limit;               // The upper 16 bits of all selector limits.
	   uint32_t base;                // The address of the first gdt_entry_t struct.
	}
	 __attribute__((packed));
	struct entry_struct
	{
		uint16_t limit_low;           // The lower 16 bits of the limit.
		uint16_t base_low;            // The lower 16 bits of the base.
		uint8_t  base_middle;         // The next 8 bits of the base.
		uint8_t access;              // Access flags, determine what ring this segment can be used in.
		uint8_t granularity;
		uint8_t  base_high;           // The last 8 bits of the base.
	}
	__attribute__((packed));
	typedef struct entry_struct entry_t;
	typedef struct ptr_struct ptr_t;
public:
	static void initialize();
	static void flush(uint32_t);
	static void setGate(int32_t,uint32_t,uint32_t,uint8_t,uint8_t);
private:
protected:
	static entry_t m_entries[5];
	static ptr_t   m_ptr;
};


class IDT
{
public:
	// A struct describing an interrupt gate.
	struct entry_struct
	{
	    uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
	    uint16_t sel;                 // Kernel segment selector.
	    uint8_t  always0;             // This must always be zero.
	    uint8_t  flags;               // More flags. See documentation.
	    uint16_t base_hi;             // The upper 16 bits of the address to jump to.
	} __attribute__((packed));

	typedef struct entry_struct entry_t;

	// A struct describing a pointer to an array of interrupt handlers.
	// This is in a format suitable for giving to 'lidt'.
	struct ptr_struct
	{
	    uint16_t limit;
	    uint32_t base;                // The address of the first element in our idt_entry_t array.
	} __attribute__((packed));

	typedef struct ptr_struct ptr_t;
public:
	static void initialize();
	static void flush(uint32_t);
	static void setGate(uint8_t,uint32_t,uint16_t,uint8_t);
private:
protected:
	static entry_t m_entries[256];
	static ptr_t   m_ptr;
};

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C" void isr0 ();
extern "C" void isr1 ();
extern "C" void isr2 ();
extern "C" void isr3 ();
extern "C" void isr4 ();
extern "C" void isr5 ();
extern "C" void isr6 ();
extern "C" void isr7 ();
extern "C" void isr8 ();
extern "C" void isr9 ();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void irq0 ();
extern "C" void irq1 ();
extern "C" void irq2 ();
extern "C" void irq3 ();
extern "C" void irq4 ();
extern "C" void irq5 ();
extern "C" void irq6 ();
extern "C" void irq7 ();
extern "C" void irq8 ();
extern "C" void irq9 ();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

#endif