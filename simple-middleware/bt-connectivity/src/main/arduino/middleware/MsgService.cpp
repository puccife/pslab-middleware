#include "MsgService.h"

#include <Arduino.h>

#define TIMEOUT_MICROS 5000000

Msg::Msg(const String& content) : mContent(content) {
}

String Msg::getContent(void) const {
  return mContent;
}

MsgService::MsgService(Stream *stream) : mStream(stream) {
}

void MsgService::sendMsg(const String& msg) const {
  char length = (char) msg.length();
  mStream->print(String(length) + msg);
}

void MsgService::sendMsg(const Msg& msg) const {
  sendMsg(msg.getContent());
}

bool MsgService::isMsgAvailable(void) const {
  return mStream->available();
}

Msg* MsgService::receiveMsg(void) {
  if (mStream->available()) {
    mContent = "";
    int size = mStream->read();
    int nDataRec = 0;
    unsigned long start = micros();
    while (nDataRec < size) {
      if (mStream->available()) {
        mContent += (char) mStream->read();
        nDataRec++;
      }
      if ((micros() - start) >= TIMEOUT_MICROS) {
        break;
      }
    }
    return new Msg(mContent);
  }
  return NULL;
}
