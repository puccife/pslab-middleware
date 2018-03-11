#ifndef __RESOURCEMANAGER__
#define __RESOURCEMANAGER__

#include "Resource.h"
#include <iterator>
#include <list>

class ResourceManager {
  public:
    bool addResource(Resource *resource);

    Resource *getResourceById(const String& id) const;

    void removeResourceById(const String& id);
  private:
    std::list<Resource *> mResources;
};

#endif /* __RESOURCEMANAGER__ */
