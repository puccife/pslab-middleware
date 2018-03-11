#ifndef __TEMPERATURESENSOR__
#define __TEMPERATURESENSOR__

struct TemperatureSensor {
  virtual int getTemperature(void) = 0;
};

#endif
