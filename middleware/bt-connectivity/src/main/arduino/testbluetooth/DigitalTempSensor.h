#ifndef __DIGITALTEMPSENSOR__
#define __DIGITALTEMPSENSOR__

#include "TemperatureSensor.h"

class DigitalTempSensor : public TemperatureSensor {
  public:
    DigitalTempSensor();
    int getTemperature();
  private:
    const int temp_address = 72; //1001000 in decimale
};

#endif
