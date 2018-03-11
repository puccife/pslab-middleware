#include "ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(const int pin) : mPin(pin) {
  pinMode(mPin, INPUT);
}

bool ButtonImpl::isPressed(void) const {
  return digitalRead(mPin) == HIGH;
}
