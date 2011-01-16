#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H
#include <machine/Device.h>

class OutputDevice : public Device
{
public:
	typedef enum
	{
		DEVICE_STATUS_UNKNOWN = -1,
		DEVICE_STATUS_OFF = 0,
		DEVICE_STATUS_ON = 1,
		DEVICE_STATUS_SUSPENDED = 2
	}Status_e;
	DeclareTypeInfo();
public:
	virtual Status_e initialize() = 0;
	virtual Status_e shutdown() = 0;
	virtual Status_e monitor() = 0;
	char W;
	Device()
	{
		W ='W';
	};
	char moo()
	{
		return 'W';
	};
};
#endif