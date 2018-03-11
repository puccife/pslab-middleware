#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"

class ButtonImpl : public Button {
  public:
    ButtonImpl(const int pin);

    bool isPressed(void) const;
  private:
    const int pin;
};

#endif /* __BUTTONIMPL__ */
