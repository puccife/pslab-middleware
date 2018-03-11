#include "DigitalTempSensor.h"
#include <Wire.h>

DigitalTempSensor::DigitalTempSensor() {
  Wire.begin(); /* lib init */
}

int DigitalTempSensor::getTemperature() {
  Wire.beginTransmission(temp_address);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(temp_address, 1);
  while (Wire.available() == 0);
  return Wire.read();
}
