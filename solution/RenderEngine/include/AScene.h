#pragma once

#include "Entity.h"

namespace sre
{

using Action = std::function<void(void*)>;

class AScene
{
protected:
    std::unordered_map<std::string, UPTR<Entity>> entities;
    static uint32_t EntityIndex;

private:
    std::string name;
    std::string label;
    std::string filePath;
    SPTR<Action> entityChangedAction;

protected:
    AScene(std::string arg_name, std::string arg_filePath);
    virtual ~AScene();

public:
    Entity* getEntity(const std::string& entityName);

protected:
    Entity* createEntity(std::string name = "", Entity* parent = nullptr, const std::string& className = "Entity");
	Entity* createEntityFromFile(std::string filePath, Entity* parent = nullptr);
	Entity* duplicateEntity(Entity* entity);
	void moveEntityToChild(const std::string& entityName, Entity* targetParent);
	void moveEntityToRoot(Entity* entity);
    void removeDestroyedEntities();
    void onSceneLoaded();

private:
    void initEntities();
    void update(float elapsedTime);
    void resolveName(std::string& entityName);
    std::string generateEntityId(const std::string& duplicateName = "");
    void onEntityChanged(void* data);
    void onSceneSaved();

friend class ScenesManager;
friend class EditorSceneTree;
friend class EditorsController;
friend class SceneLoader;
friend class EntityParser;
friend class EntityLoader;
};

} // namespace
