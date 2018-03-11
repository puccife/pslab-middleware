#ifndef __RESOURCE__
#define __RESOURCE__
#include "ArduinoJson.h"
class Resource {
  public:
    Resource(String id);
    String getRequest(void);
    void putRequest(String payload);
    String getId();
    String getState();
    
  private:
    String id;
    String state;
};

#endif /* __RESOURCE__ */
