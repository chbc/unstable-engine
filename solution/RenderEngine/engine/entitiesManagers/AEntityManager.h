#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <engine/entities/Entity.h>
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

protected:
    AEntityManager();
    virtual ~AEntityManager();

    const std::string generateEntityId();
    void removeDestroyedEntities();

public:
    void addEntity(Entity *entity, const std::string &name = "");

    Entity *createEntity();
};

} // namespace

#endif
