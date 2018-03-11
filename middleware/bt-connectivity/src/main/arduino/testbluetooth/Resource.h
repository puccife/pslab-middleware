#ifndef __RESOURCE__
#define __RESOURCE__
#include "ArduinoJson.h"

struct Resource {
    virtual String getRequest(void) = 0;
    virtual void putRequest(String payload) = 0;
};

#endif /* __RESOURCE__ */
