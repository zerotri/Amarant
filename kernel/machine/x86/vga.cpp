#include "vga.h"
#include <stdint.h>
#include <pio.h>

uint16_t* VGA::m_pVRAM = (uint16_t*)0xB8000;
void VGA::put(unsigned char c)
{
	// The background colour is black (0), the foreground is white (15).
	uint8_t backColour = 0;
	uint8_t foreColour = 15;

	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
	// The attribute byte is the top 8 bits of the word we have to send to the
	// VGA board.

	// Handle any other printable character.
	if(c >= ' ')
	{
		m_pVRAM[ m_iCursorY*80 + m_iCursorX ] = (c | attributeByte << );
		m_iCursorX++;
	}
	moveCursor(m_iCursorX, m_iCursorY);
}
void VGA::clear()
{
	m_pVRAM = (uint16_t*)0xB8000;
	// Make an attribute byte for the default colours
	uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

	int i;
	for (i = 0; i < 80*25; i++)
	{
		m_pVRAM[i] = blank;
	}

	// Move the hardware cursor back to the start.
	moveCursor(0,0);
}
void VGA::write(const char* c)
{
	int i = 0;
	while (c[i] != '\0')
	{
		put(c[i++]);
	}
}

void VGA::moveCursor(uint8_t x, uint8_t y)
{
	m_iCursorX = x;
	m_iCursorY = y;
	// The screen is 80 characters wide...
	uint16_t cursorLocation = m_iCursorY * 80 + m_iCursorX;
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}
void VGA::scroll()
{
	
}
/*static unsigned char* vramptr = (unsigned char*)0xB8000;

void kputch(const char chr)
{
   //static char* vramptr = (char*)0xB8000;
   
   *vramptr = (unsigned char)chr;
   vramptr++;
   *vramptr = 0x07;
   vramptr++;
}

void kprintf(const char* strptr)
{
   //unsigned i=0;
   char* str = (char*)strptr;
   while(1)
   {
        if(*str == '\0')
          break;
        else
        {
	 //kputch(*str);
          *vramptr = (unsigned char)*str;
          vramptr++;                  
          str++;
          *vramptr = (unsigned char)0x07;
          vramptr++;
        }
   }
   /*while (*strptr != 0 && i <1024)
   {
      kputch(*strptr);
      
      strptr++;
      i++;
   }
}*/
