#include "AbstractLed.h"
#include <Arduino.h>

AbstractLed::AbstractLed(int pin) : mPin(pin), mOn(false) {
  pinMode(getPin(), OUTPUT);
}

int AbstractLed::getPin(void) const {
  return mPin;
}

bool AbstractLed::isOn(void) const {
  return mOn;
}

void AbstractLed::setOn(bool on) {
  mOn = on;
}
