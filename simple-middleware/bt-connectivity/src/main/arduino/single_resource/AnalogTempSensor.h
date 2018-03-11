/*
   AnalogTempSensor.h

*/

#ifndef ANALOGTEMPSENSOR_H_
#define ANALOGTEMPSENSOR_H_

#include "TemperatureSensor.h"

class AnalogTempSensor: public TemperatureSensor {
  public:
    AnalogTempSensor(int pin);

    int getTemperature(void);

  private:
    int pin;
};

#endif /* ANALOGTEMPSENSOR_H_ */
