#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include <ArduinoJson.h>
#include <Stream.h>

class Msg {
  public:
    Msg(const String& content);

    String getContent(void) const;
  private:
    String mContent;
};

class MsgService {
  public:
    MsgService(Stream *stream);

    bool isMsgAvailable(void) const;

    Msg* receiveMsg(void);

    void sendMsg(const String& message) const;

    void sendMsg(const Msg& message) const;

  private:
    Stream *mStream;
    String mContent;
};

#endif /* __MSGSERVICE__ */
