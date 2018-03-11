#ifndef __CONTEXT__
#define __CONTEXT__

#include "Request.h"
#include "Response.h"

class Context {
  public:
    Context(const Request& request, const Response& response);

    Request& request(void);
    const Request& request(void) const;

    Response& response(void);
    const Response& response(void) const;
  private:
    Request mRequest;
    Response mResponse;
};

#endif /* __CONTEXT__ */
