#ifndef __RESOURCES__
#define __RESOURCES__

#include "AbstractResource.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "LedExt.h"

class ButtonResource : public AbstractResource, public ButtonImpl {
  public:
    ButtonResource(int pin, const String& id);
  protected:
    virtual void onGetRequest(Context& context) const;

    void onPutRequest(Context& context);
};

class LedResource : public AbstractResource, public Led {
  public:
    LedResource(int pin, const String& id);
  protected:
    virtual void onGetRequest(Context& context) const;

    virtual void onPutRequest(Context& context);
};

class LedExtResource : public AbstractResource, public LedExt {
  public:
    LedExtResource(int pin, const String& id);
  protected:
    void onGetRequest(Context& context) const;

    void onPutRequest(Context& context);
};

#endif /* __RESOURCES__ */
