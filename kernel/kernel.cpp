#include <kernel/machine/VideoDevice.h>
#include <kernel/machine/x86/gdt.h>
#include <kernel/machine/x86/isr.h>
#include <kernel/machine/x86/vga.h>
#include <kernel/machine/x86/paging.h>
#include <kernel/include/core/AKObject.h>
#include <memory.h>
#include <libraries/crystal/include/CSMemory.h>
#include <ctl/OrderedArray.h>
DefineTypeInfo0(Device);

extern "C" void __cxa_pure_virtual()
{
	//DO NOTHING...or print error
}
extern "C" void kmain( void* mbd, unsigned int magic);

void kmain( void* mbd, unsigned int magic )
{		
	if ( magic != 0x2BADB002 )
	{
		/* Something went not according to specs. Print an error */
		/* message and halt, but do *not* rely on the multiboot */
		/* data structure. */
	}
    initialise_paging();
	GDT::initialize();
	IDT::initialize();
	ISR::initialize();

	AKObject<VideoDevice> AudioOut;
	//Device* = (*AudioOut);
	char something = AudioOut->moo();
	//char string[] = {'H','e','l','l','o',' ','W','o','r','l','d','!','\0'};
	mbd = mbd;
    void* a = CSAllocateMemory<uint8_t>(8);
    void* b = CSAllocateMemory<uint8_t>(8);
    void* c = CSAllocateMemory<uint8_t>(8);

	VGA* screen = new VGA;
	screen->clear();
	screen->write("Hello World!");
}
