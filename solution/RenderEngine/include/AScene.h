#pragma once

#include "Entity.h"
#include <unordered_map>

namespace sre
{

class AScene
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;
    std::unordered_map<std::string, Entity*> entityAssets;
    static uint32_t EntityIndex;

private:
    std::string name;
    bool sceneLoaded;

public:
    Entity* getEntity(const std::string& arg_name);

protected:
    AScene(std::string name);
    Entity* createEntity(const std::string& name = "", Entity* parent = nullptr);
    void addEntityAsset(Entity* entityAsset);
    void removeDestroyedEntities();

private:
    void initEntities();
    void update(float elapsedTime);
    void onSceneLoaded();
    void clean();
    void release();

friend class ScenesManager;
friend class EditorSceneTree;
friend class EditorsController;
friend class SceneLoader;
friend class EntityParser;
friend class EntityLoader;
};

} // namespace
