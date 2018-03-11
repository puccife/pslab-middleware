#ifndef __PROXIMITYSENSOR__
#define __PROXIMITYSENSOR__

struct ProximitySensor {
	virtual float getDistance(void) = 0;
};

#endif
