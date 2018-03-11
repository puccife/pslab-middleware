#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include <ArduinoJson.h>
#include "SoftwareSerial.h"
#include "HardwareSerial.h"

#define MAX_MSG_SIZE 256

template<typename T>
extern String encode(const Internals::JsonPrintable<T> json) {
  char *str = "";
  json.printTo(str, MAX_MSG_SIZE);
  return String(str);
}

template<typename T>
extern String encodePriettly(const Internals::JsonPrintable<T> json) {
  char *str = "";
  json.prettyPrintTo(str, MAX_MSG_SIZE);
  return String(str);
}

class Msg {
  String content;
  public:
    Msg(const String content) {
      this->content = content;
    }

    String getContent(void) const {
      return this->content;
    }
};

class MsgService {
  public:
    MsgService(const int rxPin, const int txPin);

    void init(void);

    bool isMsgAvailable(void);

    Msg* receiveMsg(void);

    bool sendMsg(const String message);

    bool sendMsg(Msg *msg);

    template<typename T>
    bool sendMsg(const Internals::JsonPrintable<T> json) {
      return sendMsg(encode(json));
    }
  private:
    String content;
    HardwareSerial *channel;
};

#endif /* __MSGSERVICE__ */
