#ifndef __LIGHT__
#define __LIGHT__

struct Light {
  virtual void switchOn(void) = 0;

  virtual void switchOff(void) = 0;

  virtual bool isOn(void) const = 0;
};

#endif /* __LIGHT__ */
