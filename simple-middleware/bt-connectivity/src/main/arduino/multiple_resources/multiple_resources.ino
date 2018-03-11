#include <pnew.cpp>

#include <SoftwareSerial.h>

#include "RequestHandler.h"
#include "ResourceManager.h"
#include "resources.h"

SoftwareSerial *bluetoothSerial = new SoftwareSerial(2, 3);
ResourceManager *resourceManager = new ResourceManager();
RequestHandler requestHandler(MsgService(bluetoothSerial), resourceManager);

void setup(void) {
  Serial.begin(9600);
  bluetoothSerial->begin(9600);
  resourceManager->addResource(new LedExtResource(5, "led1"));
  while (!Serial);
  Serial.println("Ready!");
}

void loop(void) {
  requestHandler.checkIncomingRequest();
}
