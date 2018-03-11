#ifndef __PIR__
#define __PIR__

#include "MotionSensor.h"

class PIR : public MotionSensor {
  public:
    PIR(int pin);

    bool isDetected(void);
  private:
    int pin;
};

#endif
