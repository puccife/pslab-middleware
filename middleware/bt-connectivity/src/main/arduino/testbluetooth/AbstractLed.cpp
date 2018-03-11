#include "AbstractLed.h"
#include <Arduino.h>

AbstractLed::AbstractLed(int pin) : pin(pin), on(false) {
  pinMode(getPin(), OUTPUT);
}

int AbstractLed::getPin(void) const {
  return pin;
}

bool AbstractLed::isOn(void) const {
  return this->on;
}

void AbstractLed::setOn(bool on) {
  this->on = on;
}
