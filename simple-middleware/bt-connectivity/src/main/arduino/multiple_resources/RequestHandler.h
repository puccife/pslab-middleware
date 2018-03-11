#ifndef __REQUESTHANDLER__
#define __REQUESTHANDLER__

#include "MsgService.h"
#include "ResourceManager.h"

struct RequestData {
  String resourceId;

  String action;

  String payload;
};

class RequestHandler {
  public:
    RequestHandler(const MsgService& msgService, ResourceManager *resourceManager);

    void checkIncomingRequest(void);
  private:
    void handleRequest(const RequestData& request);

    Context *createContext(const Action& action, const JsonObject& payload);

    MsgService mMsgService;
    ResourceManager *mResourceManager;
};

#endif /* __REQUESTHANDLER__ */
