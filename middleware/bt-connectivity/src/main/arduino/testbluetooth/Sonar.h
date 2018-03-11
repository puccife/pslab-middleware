#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"

class Sonar: public ProximitySensor {
public:
	Sonar(int echoPin, int trigPin);

	float getDistance(void);
private:
	int echoPin, trigPin;
};

#endif
