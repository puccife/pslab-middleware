#include "Request.h"

Request::Request(const Action& action, const JsonObject& payload): mAction(action), mPayload(payload) {
}

const Action& Request::action(void) const {
  return mAction;
}

const JsonObject& Request::payload(void) const {
  return mPayload;
}
