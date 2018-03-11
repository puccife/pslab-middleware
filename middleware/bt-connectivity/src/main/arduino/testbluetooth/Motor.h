/*
   Motor.h

*/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "ServoTimer2.h"

class Motor {
  public:

    Motor(int pin);
    
    const int MIN_MOTOR_ROTATION = 0;
    const int MAX_MOTOR_ROTATION = 180;

    void close();
    void rotate(int angle);

  private:
    ServoTimer2 m1;
    
    void init(int pin);
};

#endif /* MOTOR_H_ */
