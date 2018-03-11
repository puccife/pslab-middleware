/*
   CommunicationHandler.cpp
*/

#include "CommunicationHandler.h"
#include <MemoryFree.h>
#include "ResourceManager.h"
#include "MsgService.h"

#define RXD_PIN 2
#define TXD_PIN 3
#define ROOT_ARRAY_NUM 0
#define ROOT_VALUES_NUM 5
#define BUFFER_SIZE 200

CommunicationHandler comHandler;
MsgService BluetoothService(RXD_PIN, TXD_PIN);

void CommunicationHandler::init(Resource* resource) {
  BluetoothService.init();
  this->resource = resource;
}

void CommunicationHandler::monitorResource() {
  if (BluetoothService.isMsgAvailable()) { 
    StaticJsonBuffer<200> jsonBuffer;
    Msg* msg = BluetoothService.receiveMsg();
    String input = msg->getContent();
    delete msg;
    JsonObject& request = jsonBuffer.parseObject(input);
    String resourceId = request["resourceId"];
    String action = request["action"];
    if(action=="WRITE") {
      JsonObject& payloadRequest = request["payload"];
      String payload;
      payloadRequest.printTo(payload);
      resource->putRequest(payload);
    }
    String getResponse = resource->getRequest();
    BluetoothService.sendMsg(&Msg(getResponse));
  }
}
