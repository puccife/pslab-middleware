#include "Resource.h"

Resource::Resource(const String& id) : mId(id) {
}

Resource::~Resource(void) {
}

String Resource::getId(void) const {
  return mId;
}
