#pragma once

#include "Entity.h"
#include <unordered_map>

namespace sre
{

class AScene
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;

private:
    std::string name;
    bool sceneLoaded;

public:
    Entity* getEntity(const std::string& arg_name);

protected:
    AScene(std::string name);
    Entity* createEntity(uint32_t &index, const std::string& name = "", Entity* parent = nullptr);
    void removeDestroyedEntities();

private:
    void update(uint32_t elapsedTime);

    void onSceneLoaded();
    void destroyAllEntities();

    void release();

friend class ScenesManager;
friend class EditorSceneTree;
};

} // namespace
