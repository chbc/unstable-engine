#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Entity.h"
#include <unordered_map>

namespace sre
{

class AEntityManager
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;
    std::unordered_map<Entity *, UPTR<Entity>> entitiesToBeAdded;

private:
    uint32_t entityIndex;
    bool sceneLoaded;

public:
    SRE_API virtual void addEntity(Entity *entity, const std::string &name = "");
	SRE_API Entity *createEntity();

protected:
    AEntityManager();
    virtual ~AEntityManager();

    const std::string generateEntityId();
    void removeDestroyedEntities();

private:
    void onSceneLoaded();

friend class RenderEngine;
};

} // namespace

#endif
