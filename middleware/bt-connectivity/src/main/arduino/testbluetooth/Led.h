#ifndef __LED__
#define __LED__

#include "AbstractLed.h"

class Led: public AbstractLed {
  public:
    Led(const int pin);

    void switchOn(void);

    void switchOff(void);
};

#endif /* __LED__ */
