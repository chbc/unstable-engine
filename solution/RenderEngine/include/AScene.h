#pragma once

#include "Entity.h"

namespace sre
{

class AScene
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;
    static uint32_t EntityIndex;
    class RenderManager* renderManager;

private:
    std::string name;
    bool sceneLoaded;

public:
    Entity* getEntity(const std::string& arg_name);

protected:
    AScene(std::string name);
    virtual ~AScene();
    Entity* createEntity(std::string name = "", Entity* parent = nullptr, const std::string& className = "Entity", const std::string& fileName = "");
    void removeDestroyedEntities();

private:
    void initEntities();
    void update(float elapsedTime);
    void onSceneLoaded();
    void resolveName(std::string& name);
    std::string generateEntityId(const std::string& duplicateName = "");

friend class ScenesManager;
friend class EditorSceneTree;
friend class EditorsController;
friend class SceneLoader;
friend class EntityParser;
friend class EntityLoader;
};

} // namespace
