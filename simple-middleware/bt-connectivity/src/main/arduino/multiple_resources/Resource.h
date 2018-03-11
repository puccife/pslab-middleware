#ifndef __RESOURCE__
#define __RESOURCE__

#include "Context.h"

class Resource {
  public:
    Resource(const String& id);

    virtual ~Resource(void);

    String getId(void) const;

    virtual void onRequest(Context& context) = 0;
  private:
    String mId;
};

#endif /* __RESOURCE__ */
