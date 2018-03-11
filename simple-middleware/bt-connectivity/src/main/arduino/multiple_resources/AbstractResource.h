#ifndef __ABSTRACTRESOURCE__
#define __ABSTRACTRESOURCE__

#include "Resource.h"

class AbstractResource : public Resource {
  public:
    AbstractResource(const String& id);

    void onRequest(Context& context);
  protected:
    virtual void onGetRequest(Context& context) const;

    virtual void onPutRequest(Context& context);
};

#endif /* __ABSTRACTRESOURCE__ */
