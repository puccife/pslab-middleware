#include "LedExt.h"
#include <Arduino.h>

LedExt::LedExt(const int pin) : LedExt(pin, 127) {
}

LedExt::LedExt(const int pin, const int intensity) : AbstractLed(pin) {
  setIntensity(intensity);
}

void LedExt::switchOn(void) {
  analogWrite(getPin(), getIntensity());
  setOn(true);
}

void LedExt::switchOff(void) {
  digitalWrite(getPin(), LOW);
  setOn(false);
}

bool LedExt::isOn(void) const {
  return AbstractLed::isOn();
}

int LedExt::getIntensity(void) const {
  return intensity;
}

void LedExt::setIntensity(const int intensity) {
  if (intensity < 0) {
    this->intensity = 0;
  } else if (intensity > 255) {
    this->intensity = 255;
  } else {
    this->intensity = intensity;
  }
  if (isOn()) {
    analogWrite(getPin(), getIntensity());
  }
}
