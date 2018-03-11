#ifndef __LED_EXT__
#define __LED_EXT__

#include "AbstractLed.h"
#include "LightExt.h"

class LedExt : public AbstractLed, public LightExt {
  public:
    LedExt(int pin);

    LedExt(int pin, int intensity);

    void switchOn(void);

    void switchOff(void);

    bool isOn(void) const;

    int getIntensity(void) const;

    void setIntensity(int intensity);
  private:
    int mIntensity;
};

#endif
