/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
#ifndef _ARCH_I386_PIO_H_
#define _ARCH_I386_PIO_H_

typedef unsigned short i386_ioport_t;

#if defined(__GNUC__)
static __inline__ unsigned int	inl(
				i386_ioport_t port)
{
	unsigned int datum;
	__asm__ volatile("inl %w1, %0" : "=a" (datum) : "Nd" (port));
	return(datum);
}

static __inline__ unsigned short inw(
				i386_ioport_t port)
{
	unsigned short datum;
	__asm__ volatile("inw %w1, %w0" : "=a" (datum) : "Nd" (port));
	return(datum);
}

static __inline__ unsigned char inb(
				i386_ioport_t port)
{
	unsigned char datum;
	__asm__ volatile("inb %w1, %b0" : "=a" (datum) : "Nd" (port));
	return(datum);
}

static __inline__ void outl(
				i386_ioport_t port,
				unsigned int datum)
{
	__asm__ volatile("outl %0, %w1" : : "a" (datum), "Nd" (port));
}

static __inline__ void outw(
				i386_ioport_t port,
				unsigned short datum)
{
	__asm__ volatile("outw %w0, %w1" : : "a" (datum), "Nd" (port));
}

static __inline__ void outb(
				i386_ioport_t port,
				unsigned char datum)
{
	__asm__ volatile("outb %b0, %w1" : : "a" (datum), "Nd" (port));
}
#endif /* defined(__GNUC__) */
#endif /* _ARCH_I386_PIO_H_ */
