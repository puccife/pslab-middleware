#ifndef __RESOURCEMANAGER__
#define __RESOURCEMANAGER__

#include "Resource.h"
#include <iterator>
#include <list>

class ResourceManagerClass {
  public:
    ResourceManagerClass(void);

    bool addResource(const Resource *resource);

    Resource *getResource(const int id, const int category) const;
    Resource *getResourceById(const int id) const;
    std::list<Resource *> getResourceByCategory(const int category) const;

    void removeResource(const int id, const int category);
    void removeResourceById(const int id);
    void removeResourceByCategory(const int category);
  private:
    std::list<Resource *> resources;
};

extern ResourceManagerClass ResourceManager;

#endif /* __RESOURCEMANAGER__ */
