#pragma once

#include "Scene.h"
#include "GUIScene.h"
#include "ASingleton.h"
#include "RefreshMeshesMessage.h"

namespace sre
{

class ScenesManager : public ASingleton
{
protected:
    UPTR<Scene> scene;
    UPTR<GUIScene> guiScene;

private:
    SPTR<Action> refreshMeshesAction;

protected:
    void init() override;

public:
    SRE_API std::string getMainSceneName();
	SRE_API Entity* createEntity(std::string name = "", Entity* parent = nullptr);
    SRE_API Entity* getEntity(const std::string& name);
    SRE_API Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    SRE_API Entity* createOrthoCamera(Entity* parent = nullptr, bool isMainCamera = true);
    SRE_API DirectionalLightComponent* createDirectionalLight(const std::string& name = "", Entity* parent = nullptr);
    SRE_API PointLightComponent* createPointLight(const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* createGUIImageEntity(const std::string& filePath, const std::string& name = "");
    SRE_API Entity* createGUIImageEntity(const std::string& filePath, const glm::vec2& normalizedSize, const std::string& name = "");
    SRE_API Entity* createGUIImageEntityFromAtlas(const std::string& filePath, const std::string& imageId, const std::string& name = "");
    SRE_API Entity* createGUITextEntity(const std::string fontFile, const std::string& name = "", uint32_t maxItems = 100u);
    SRE_API Entity* raycast(const Ray& ray, float maxDistance = 1000);
	SRE_API Entity* raycastFromScreen(const glm::vec2& mousePosition, const glm::vec2& viewportSize, float maxDistance = 1000);

private:
    void initEntities();
    void update(float elapsedTime);
    void loadScene(const char* scenePath);
    void loadGuiScene(const char* scenePath);
    void saveScene(std::string scenePath = "");
    void saveGuiScene(std::string scenePath = "");
    bool isSceneStored();
    bool isGuiSceneStored();
    bool isBaseSceneStored(AScene* baseScene);
    Entity* createMeshEntity(const char* filePath, const char* meshName);
    AScene* getScene();
    AScene* getGuiScene();
    void onRefreshMeshes();
    void removeDestroyedEntities();
    void cleanUp();
    void preRelease() override;

friend class AExecutionStrategy;
friend class ApplicationStrategy;
friend class EditorSceneTree;
friend class EditorsController;
friend class SingletonsManager;
};

} // namespace
