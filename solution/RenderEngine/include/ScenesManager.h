#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Scene.h"
#include "GUIScene.h"
#include "ASingleton.h"

namespace sre
{

class ScenesManager : public ASingleton
{
protected:
    UPTR<Scene> scene;
    UPTR<GUIScene> guiScene;

public:
    SRE_API Scene* createScene(const std::string& name);
    SRE_API std::string getMainSceneName();
	SRE_API Entity* createEntity(const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* getEntity(const std::string& name);

    SRE_API Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    SRE_API Entity* createOrthoCamera(Entity* parent = nullptr, bool isMainCamera = true);

    // light //
    SRE_API DirectionalLightComponent* createDirectionalLight(const std::string& name = "", Entity* parent = nullptr);
    SRE_API PointLightComponent* createPointLight(const std::string& name = "", Entity* parent = nullptr);

    // GUI //
    SRE_API Entity* createGUIImageEntity(const std::string& fileName);
    SRE_API Entity* createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize);
    SRE_API Entity* createGUIImageEntityFromAtlas(const std::string& fileName, const std::string& imageId);
    SRE_API Entity* createGUITextEntity(const std::string fontFile, uint32_t maxItems = 100u);

protected:
    void init() override;

private:
    void loadScene(const char* sceneName);
    void saveScenes();
    void initEntities();
    void update(float elapsedTime);
    Entity* createMeshEntity(const char* name, const char* filaName);
    void removeDestroyedEntities();
    void cleanUp();
    void preRelease() override;

friend class RenderEngine;
friend class AExecutionStrategy;
friend class ApplicationStrategy;
friend class EditorSceneTree;
friend class EditorsController;
friend class SingletonsManager;
};

} // namespace

#endif
