#include "AbstractResource.h"

AbstractResource::AbstractResource(const String& id) : Resource(id) {
}

void AbstractResource::onRequest(Context& context) {
  switch (context.request().action()) {
    case Action::READ:
      onGetRequest(context);
      break;
    case Action::WRITE:
      onPutRequest(context);
      break;
    case Action::INVALID_ACTION:
    default:
      break;
  }
}

void AbstractResource::onGetRequest(Context& context) const {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& response = jsonBuffer.createObject();
  response["error"] = getId() + " can't perform READ request";
  String msg;
  response.printTo(msg);
  context.response().end(msg);
}

void AbstractResource::onPutRequest(Context& context) {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& response = jsonBuffer.createObject();
  response["error"] = getId() + " can't perform WRITE request";
  String msg;
  response.printTo(msg);
  context.response().end(msg);
}
