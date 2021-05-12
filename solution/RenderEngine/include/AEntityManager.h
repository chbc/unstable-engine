#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Entity.h"
#include "StringUtils.h"
#include <unordered_map>

namespace sre
{

class AEntityManager
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;

private:
    uint32_t entityIndex;
    bool sceneLoaded;

public:
	SRE_API Entity* createEntity(const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* getEntity(const std::string& name);

protected:
    AEntityManager();
    void removeDestroyedEntities();

private:
    void onSceneLoaded();
    void destroyAllEntities();

    void release();

friend class RenderEngine;
friend class EditorSceneTree;
};

} // namespace

#endif
