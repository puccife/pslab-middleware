#ifndef __BUTTON__
#define __BUTTON__

struct Button {
  virtual bool isPressed(void) const = 0;
};

#endif /* __BUTTON__ */
