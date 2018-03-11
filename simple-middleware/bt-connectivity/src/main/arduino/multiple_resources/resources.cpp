#include "resources.h"

#include <MemoryFree.h>
#include <Arduino.h>

String stateToString(const bool state);

const String STATE_ON = "on";
const String STATE_OFF = "off";

ButtonResource::ButtonResource(int pin, const String& id) : AbstractResource(id), ButtonImpl(pin) {
}

void ButtonResource::onGetRequest(Context& context) const {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& response = jsonBuffer.createObject();
  response["pressed"] = isPressed();
  String msg;
  response.printTo(msg);
  Serial.println(msg);
  context.response().end(msg);
}

void ButtonResource::onPutRequest(Context& context) {
  AbstractResource::onPutRequest(context);
}

LedResource::LedResource(int pin, const String& id) : AbstractResource(id), Led(pin) {
}

void LedResource::onGetRequest(Context& context) const {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& response = jsonBuffer.createObject();
  response["state"] = stateToString(isOn());
  String msg;
  response.printTo(msg);
  Serial.println(msg);
  context.response().end(msg);
}

void LedResource::onPutRequest(Context& context) {
  const JsonObject& payload = context.request().payload();
  if (payload.containsKey("state")) {
    String state = payload["state"];
    if (state == STATE_ON) {
      switchOn();
    } else if (state == STATE_OFF) {
      switchOff();
    }
  }
  onGetRequest(context);
}

LedExtResource::LedExtResource(int pin, const String& id) : AbstractResource(id), LedExt(pin) {
}

void LedExtResource::onGetRequest(Context& context) const {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& response = jsonBuffer.createObject();
  Serial.println(freeMemory());
  const bool on = isOn();
  response["state"] = stateToString(on);
  if (on) {
    response["intensity"] = getIntensity();
  }
  String msg;
  response.printTo(msg);
  Serial.println(msg);
  context.response().end(msg);
}

void LedExtResource::onPutRequest(Context& context) {
  const JsonObject& payload = context.request().payload();
  if (payload.containsKey("intensity")) {
    const int intensity = payload["intensity"];
    setIntensity(intensity);
  }
  if (payload.containsKey("state")) {
    String state = payload["state"];
    if (state ==  STATE_ON) {
      switchOn();
    } else if (state == STATE_OFF) {
      switchOff();
    }
  }
  onGetRequest(context);
}
   
String stateToString(const bool state) {
  return state ? STATE_ON : STATE_OFF;
}
