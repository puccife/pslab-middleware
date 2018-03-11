#ifndef __RESPONSE__
#define __RESPONSE__

#include "MsgService.h"

class Response {
  public:
    Response(const MsgService& msgService);

    void end();

    void end(const String& data);

    bool ended(void) const;

    Response& write(const String& data);
  private:
    const MsgService& mMsgService;
    String mData;
    bool mEnded;
};

#endif /* __RESPONSE__ */
