#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H
#include <machine/Device.h>
#include <stdint.h>
class VideoDevice : public Device
{
public:
	struct
	{
		uint32_t width;
		uint32_t height;
		uint32_t bitdepth;
	};
	virtual Status_e initialize()
	{
		return DEVICE_STATUS_UNKNOWN;
	};
	virtual Status_e shutdown()
	{
		return DEVICE_STATUS_UNKNOWN;
	};
	virtual Status_e monitor()
	{
		return DEVICE_STATUS_UNKNOWN;
	};
private:
protected:
};
#endif