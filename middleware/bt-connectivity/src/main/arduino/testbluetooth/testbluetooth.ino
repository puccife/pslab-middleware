#include "CommunicationHandler.h"
#include "LedResource.h"
LedResource* resource;

void setup() {
  resource = new LedResource(4);
  comHandler.init(resource);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ready!");
}

void loop() {
  comHandler.monitorResource();
}

