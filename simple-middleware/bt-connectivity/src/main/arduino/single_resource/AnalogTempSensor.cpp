/*
   AnalogTempSensor.cpp

*/

#include <Arduino.h>

#include "AnalogTempSensor.h"

#define REFERENCE_VOLTAGE_ANALOG_INPUT 1100.0
#define MV_PER_DEGREE_CELSIUS 10
#define VALUES_RANGE 1024

AnalogTempSensor::AnalogTempSensor(int pin) :
  pin(pin) {
  pinMode(pin, INPUT);
}

int AnalogTempSensor::getTemperature(void) {

  /* Default analog voltage reference (5V), does not yield high resolution.
    Arduino UNO allows to sample 10 bit analog signals, ie 1024 possible values.
    If the input is from 0 to 5V it means that we 5/1023 = 0.0048875 ie Arduino UNO
    is able to measure voltages in steps of approximately 5mV (4.88).
    Since the LM35 provides a variation of 10mV / C it becomes evident that Arduino
    will have a reading accuracy of about half a degree (5/10 = 0.5),
    regardless of what is the actual precision of the sensor.
    If the sensor provides 10mV per degree and the maximum temperature is 150°C means
    that the sensor will produce an output voltage of 0 to 1.5V.
    From the proportion 1.5: x = 5:1024 we get about 307 which means that our Arduino
    will read values ​​between 0 and 307 for which the remaining 716, to reach 1024,
    will be entirely unused thing which obviously reduces the accuracy of the measure.
    If you change aRef to 1.1V, you will get almost the highest resolution possible but
    it must be absolutely avoided taking on the analog inputs a voltage higher than 1.1V
    otherwise the possibility of damage irreparably Arduino.

    The original equation came from taking the reading, finding what percentage of the range (1024) it is,
    multiplying that by the range itself(aRef, or 5000 mV), and dividing by ten
    (10 mV per degree Celcius, according to the datasheet).
  */
  return (REFERENCE_VOLTAGE_ANALOG_INPUT * analogRead(pin)) / VALUES_RANGE / MV_PER_DEGREE_CELSIUS;
}

