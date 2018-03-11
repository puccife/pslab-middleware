#include "Response.h"

Response::Response(const MsgService& msgService): mMsgService(msgService), mData(""), mEnded(false) {
}

void Response::end(void) {
  if (!ended()) {
    mMsgService.sendMsg(mData);
  }
  mEnded = true;
}

void Response::end(const String& data) {
  write(data);
  end();
}

bool Response::ended(void) const {
  return mEnded;
}

Response& Response::write(const String& data) {
  if (!ended()) {
    mData += data;
  }
  return *this;
}
