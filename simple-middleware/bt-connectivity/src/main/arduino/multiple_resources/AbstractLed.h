#ifndef __ABSTRACTLED__
#define __ABSTRACTLED__

#include "Light.h"

class AbstractLed : public Light {
  public:
    virtual bool isOn(void) const;
  protected:
    AbstractLed(const int pin);

    int getPin(void) const;

    void setOn(bool on);
  private:
    const int mPin;
    bool mOn;
};

#endif /* __ABSTRACTLED__ */
