#ifndef __LIGHTEXT__
#define __LIGHTEXT__

struct LightExt : public Light {
  virtual int getIntensity(void) const = 0;

  virtual void setIntensity(int) = 0;
};

#endif /* __LIGHTEXT__ */
