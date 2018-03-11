/*
   Motor.cpp

   It encapsulates a simple servo motor and provides methods to control it.

*/

#include "Motor.h"

Motor::Motor(int pin){
  init(pin);
}

void Motor::init(int pin) {
  m1.attach(pin);
}

void Motor::close() {
  m1.detach();
}

void Motor::rotate(int angle) {
  m1.write(angle);
}
