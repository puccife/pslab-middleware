/*
   CommunicationHandler.h
   Provides functions to communicate with Server as decoding/encoding JSON messages.
*/

#ifndef __COMMUNICATIONHANDLER__
#define __COMMUNICATIONHANDLER__

#include <Arduino.h>
#include <ArduinoJson.h>
#include "resources.h"
#include "ResourceManager.h"

class CommunicationHandler {
  public:
  
    void monitorResource();
    void init(Resource *resource);

  private:
  
    Resource* resource;
};

extern CommunicationHandler comHandler;

#endif /* __COMMUNICATIONHANDLER__ */
