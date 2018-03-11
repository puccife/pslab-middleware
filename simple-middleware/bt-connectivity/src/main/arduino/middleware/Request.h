#ifndef __REQUEST__
#define __REQUEST__

#include <ArduinoJson.h>

enum Action {
  WRITE, READ, INVALID_ACTION
};

class Request {
  public:
    Request(const Action& action, const JsonObject& payload);

    const Action& action(void) const;

    const JsonObject& payload(void) const;
  private:
    const Action&  mAction;
    const JsonObject&  mPayload;
};

#endif /* __REQUEST__ */
