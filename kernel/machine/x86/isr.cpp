//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//

#include "pio.h"
#include "isr.h"
#include <memory.h>

typedef enum
{
	PORT_MASTER = 0x20,
	PORT_SLAVE = 0xA0
}ports;

typedef enum
{
	SIGNAL_RESET = 0x20
}signals;
ISR::isr_t ISR::m_pInterruptHandlers[256];

void ISR::registerInterruptHandler(uint8_t n, ISR::isr_t handler)
{
    m_pInterruptHandlers[n] = handler;
}

extern "C" void isr_handler(ISR::registers_t regs)
{
	ISR::isrHandler(regs);
}
extern "C" void irq_handler(ISR::registers_t regs)
{
	ISR::irqHandler(regs);
}
// This gets called from our ASM interrupt handler stub.
void ISR::isrHandler(ISR::registers_t regs)
{
    if (m_pInterruptHandlers[regs.int_no] != 0)
    {
        ISR::isr_t handler = m_pInterruptHandlers[regs.int_no];
        handler(regs);
    }
    else
    {
        //monitor_write("unhandled interrupt: ");
        //monitor_write_dec(regs.int_no);
        //monitor_put('\n');
    }
}

// This gets called from our ASM interrupt handler stub.
void ISR::irqHandler(ISR::registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(PORT_SLAVE, SIGNAL_RESET);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(PORT_MASTER, SIGNAL_RESET);

    if (m_pInterruptHandlers[regs.int_no] != 0)
    {
        ISR::isr_t handler = m_pInterruptHandlers[regs.int_no];
        handler(regs);
    }

}

void ISR::initialize()
{
	memset((uint8_t*)&m_pInterruptHandlers, 0, sizeof(ISR::isr_t)*256);
}
