#include "Context.h"

Context::Context(const Request& request, const Response& response) : mRequest(request), mResponse(response) {
}

Request& Context::request(void) {
  return mRequest;
}

const Request& Context::request(void) const {
  return mRequest;
}

Response& Context::response(void) {
  return mResponse;
}

const Response& Context::response(void) const {
  return mResponse;
}
