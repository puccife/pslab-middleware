/*Simple class that manage the reading of the values detected by the PIR sensor.*/

#include "PIR.h"
#include "Arduino.h"

PIR::PIR(int pin) : pin(pin) {
  pinMode(pin, INPUT);
}

bool PIR::isDetected(void) {
  return digitalRead(pin) == HIGH;
}
