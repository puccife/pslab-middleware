#include "RequestHandler.h"

#include <MemoryFree.h>
#include <Arduino.h>

const String ACTION_READ = "READ";
const String ACTION_WRITE = "WRITE";

bool deserialize(RequestData& requestData, const String& json);

RequestHandler::RequestHandler(const MsgService& msgService, ResourceManager *resourceManager)
  : mMsgService(msgService)
  , mResourceManager(resourceManager) {
}

void RequestHandler::checkIncomingRequest(void) {
  bool available = false;
  if (mMsgService.isMsgAvailable()) {
    Serial.println(freeMemory());
    available = true;
    Msg *msg = mMsgService.receiveMsg();
    const String& content = msg->getContent();
    delete msg;
    RequestData requestData;
    if (deserialize(requestData, content)) {
      handleRequest(requestData);
    } else {
      Serial.println("Parse object failed!");
      StaticJsonBuffer<100> jsonBuffer;
      JsonObject& response = jsonBuffer.createObject();
      response["error"] = "Could not parse " + content;
      String msg;
      response.printTo(msg);
      mMsgService.sendMsg(msg);
    }
  }
  if (available) {
    Serial.println(freeMemory());
  }
}

void RequestHandler::handleRequest(const RequestData& requestData) {
  const String& resourceId = requestData.resourceId;
  Resource *resource = mResourceManager->getResourceById(requestData.resourceId);
  if (resource) {
    Action action = Action::INVALID_ACTION;
    if (requestData.action == ACTION_READ) {
      action = Action::READ;
    } else if (requestData.action == ACTION_WRITE) {
      action = Action::WRITE;
    } else {
      StaticJsonBuffer<100> jsonBuffer;
      JsonObject& response = jsonBuffer.createObject();
      response["error"] = "Invalid action: " + requestData.action;
      String msg;
      response.printTo(msg);
      mMsgService.sendMsg(msg);
      return;
    }
    StaticJsonBuffer<100> jsonBuffer;
    const JsonObject& payload = jsonBuffer.parseObject(requestData.payload);
    Context *context = createContext(action, payload);
    resource->onRequest(*context);
    delete context;
  } else {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();
    response["error"] = "Could not find resource with ID: " + resourceId;
    String msg;
    response.printTo(msg);
    mMsgService.sendMsg(msg);
  }
}

Context *RequestHandler::createContext(const Action& action, const JsonObject& payload) {
  return new Context(Request(action, payload), Response(mMsgService));
}

bool deserialize(RequestData& data, const String& json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& requestJson = jsonBuffer.parseObject(json);
    // const char *resourceId = requestJson["resourceId"];
    data.resourceId = requestJson["resourceId"].as<const char *>();
    // const char *action = requestJson["action"];
    data.action = requestJson["action"].as<const char *>();
    if (requestJson.containsKey("payload")) {
      requestJson["payload"].printTo(data.payload);
    } else {
      data.payload = "{}";
    }
    return requestJson.success();
}
