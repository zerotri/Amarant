#ifndef MACHINE_H
#define MACHINE_H
#include <machine/Device.h>

class Machine
{
public:
	static Machine* instance();
	virtual void initialize() = 0;
	virtual void shutdown() = 0;
protected:
	
private:
};
#endif