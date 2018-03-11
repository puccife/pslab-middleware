#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

struct LightSensor{
	virtual int getBrightness() = 0;
};

#endif
