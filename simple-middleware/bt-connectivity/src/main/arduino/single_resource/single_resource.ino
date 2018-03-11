#include "CommunicationHandler.h"

Resource* resource;

void setup() {
  resource = new Resource("led");
  comHandler.init(resource);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ready!");
}

void loop() {
  comHandler.monitorResource();
}

