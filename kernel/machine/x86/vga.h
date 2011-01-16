#ifndef VGA_H
#define VGA_H
#include <stdint.h>

//void kputch(const char chr);
//void kprintf(const char* strptr);

class VGA
{
public:
	void put(unsigned char c);
	void clear();
	void write(const char* c);
	
	//
	void moveCursor(uint8_t x, uint8_t y);
	void scroll();
protected:
	uint8_t m_iCursorX;
	uint8_t m_iCursorY;
	static uint16_t* m_pVRAM;
private:
};

#endif