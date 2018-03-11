#include "Led.h"

#include <Arduino.h>

Led::Led(const int pin) : AbstractLed(pin) {
}

void Led::switchOn(void) {
  digitalWrite(getPin(), HIGH);
  setOn(true);
}

void Led::switchOff(void) {
  digitalWrite(getPin(), LOW);
  setOn(false);
}
