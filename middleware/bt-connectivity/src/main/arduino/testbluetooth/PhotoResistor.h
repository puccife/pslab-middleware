#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include <Arduino.h>
#include "LightSensor.h"

class PhotoResistor: public LightSensor{

public:
  PhotoResistor(const int pin);
	int getBrightness();	

private:
	int pin;
};

#endif
