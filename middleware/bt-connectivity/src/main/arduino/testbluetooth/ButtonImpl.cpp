#include "ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(const int pin) : pin(pin) {
  pinMode(pin, INPUT);
}

bool ButtonImpl::isPressed(void) const {
  return digitalRead(pin) == HIGH;
}
