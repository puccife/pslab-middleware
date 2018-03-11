#include "ResourceManager.h"

static bool isSameId(const Resource *resource, const String& id);

class FindById {
  public:
    FindById(const String& id);

    bool operator()(const Resource *resource);
  private:
    String mId;
};

bool ResourceManager::addResource(Resource *resource) {
  if (resource && !getResourceById(resource->getId())) {
    mResources.push_back(resource);
    return true;
  }
  return false;
}

Resource *ResourceManager::getResourceById(const String& id) const {
  for (std::list<Resource *>::const_iterator it = mResources.begin(); it != mResources.end(); ++it) {
    Resource *resource = *(it);
    if (resource != NULL && isSameId(resource, id)) {
      return resource;
    }
  }
  return NULL;
}

void ResourceManager::removeResourceById(const String& id) {
  mResources.remove_if(FindById(id));
}

bool isSameId(const Resource *resource, const String& id) {
  return resource->getId() == id;
}
FindById::FindById(const String& id) : mId(id) {
}

bool FindById::operator()(const Resource *resource) {
  return isSameId(resource, mId);
}
