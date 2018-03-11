#include "Resource.h"
#include "Arduino.h"

Resource::Resource(String id) {
  this->id = id;
  this->state = "off";
}

String Resource::getRequest(void) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = this->getId();
  root["state"] = this->getState();
  String output;
  root.printTo(output);
  return output;
}

void Resource::putRequest(String payload) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& request = jsonBuffer.parseObject(payload);
  String state = request["state"];
  this->state = state;
}

String Resource::getId() {
  return this->id;
}

String Resource::getState() {
  return this->state;
}


