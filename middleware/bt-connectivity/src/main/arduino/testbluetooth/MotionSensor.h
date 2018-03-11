#ifndef __MOTIONSENSOR__
#define __MOTIONSENSOR__

struct MotionSensor {
  virtual bool isDetected(void) = 0;
};

#endif
