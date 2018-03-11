#include "MsgService.h"

#include <Arduino.h>

#define TIMEOUT_MICROS 5000000

MsgService::MsgService(const int rxPin, const int txPin) {
  //channel = new SoftwareSerial(rxPin, txPin);
  channel = &Serial;
}

void MsgService::init(void) {
  content.reserve(MAX_MSG_SIZE);
  channel->begin(9600);
}

bool MsgService::sendMsg(const String msg) {
  int len = msg.length();
  byte output[MAX_MSG_SIZE];
  if (len >= 0 && len <= MAX_MSG_SIZE) {
    output[0] = ((byte) len) + 1;
    msg.getBytes((output + 1), len + 1);
    channel->write((const char *) output, len + 1);
    return true;
  } else {
    return false;
  }
}

bool MsgService::sendMsg(Msg *msg) {
  byte output[256];
  String content = msg->getContent();
  int len = content.length();
  if (len >= 0 && len <= 255) {
    output[0] = (byte) len;
    content.getBytes((output + 1), len + 1);
    channel->write((const char*)output, len + 1);
    return true;
  } else {
    return false;
  }
}

bool MsgService::isMsgAvailable(void) {
  return channel->available();
}

Msg* MsgService::receiveMsg(void) {
  if (channel->available()) {
    content = "";
    int size = channel->read();
    // Serial.println("Receiving message of size " + size);
    int nDataRec = 0;
    unsigned long start = micros();
    while (nDataRec < size) {
      if (channel->available()) {
        content += (char)channel->read();
        nDataRec++;
      }
      if ((micros() - start) >= TIMEOUT_MICROS) {
        return NULL;
      }
    }
    return new Msg(content);
  }
  return NULL;
}
