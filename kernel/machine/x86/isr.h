#ifndef ISR_H
#define ISR_H
#include <stdint.h>

inline uint8_t IRQ(int IRQNumber)
{
	return IRQNumber + 32;
}
class ISR
{
public:
	enum
	{
		IRQ0 = 32, IRQ1 = 33, IRQ2 = 34, IRQ3 = 35,
		IRQ4 = 36, IRQ5 = 37, IRQ6 = 38, IRQ7 = 39,
		IRQ8 = 40, IRQ9 = 41, IRQ10 = 42, IRQ11 = 43,
		IRQ12 = 44, IRQ13 = 45, IRQ14 = 46, IRQ15 = 47
	}IRQ;
	typedef struct registers
	{
	    uint32_t ds;                  // Data segment selector
	    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
	    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
	} registers_t;
	
	typedef void (*isr_t)(registers_t);
	
public:
	static void registerInterruptHandler(uint8_t n, isr_t handler);
	static void isrHandler(registers_t regs);
	static void irqHandler(registers_t regs);
	static void initialize();
	static isr_t m_pInterruptHandlers[256];
};
#endif