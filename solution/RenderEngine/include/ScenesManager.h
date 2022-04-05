#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Scene.h"
#include "GUIScene.h"

namespace sre
{

/* XXX
* MUDAR PARA AScenesManager
* CRIAR UMA CENA PADRÃO
* REDIRECIONAR OS MÉTODOS PRA DENTRO DE Scene
* TRANSFERIR O "entities" PRA Scene
* 
*/ 
class ScenesManager
{
protected:
    UPTR<Scene> runtimeScene;
    VECTOR_UPTR<Scene> scenes;
    UPTR<GUIScene> guiScene;

private:
    uint32_t entityIndex;

public:
	SRE_API Entity* createEntity(const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* getEntity(const std::string& name);

    SRE_API Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    SRE_API Entity* createOrthoCamera(Entity* parent = nullptr, bool isMainCamera = true);

    // renderables //
    SRE_API Entity* createPlaneEntity(const glm::vec2& size, float tileMultiplier = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* createCubeEntity(float size = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity* createModelEntity(const std::string& fileName, const std::string& name = "", Entity* parent = nullptr);

    // light //
    SRE_API DirectionalLightComponent* createDirectionalLight(const std::string& name = "", Entity* parent = nullptr);
    SRE_API PointLightComponent* createPointLight(const std::string& name = "", Entity* parent = nullptr);

    // camera //
    SRE_API class CameraComponent* getMainCamera();
    SRE_API Entity* createMeshEntity(MeshData* objectData, const std::string& name = "", Entity* parent = nullptr);
    SRE_API void setMainCamera(CameraComponent* camera);

    // GUI //
    SRE_API Entity* createGUIImageEntity(const std::string& fileName);
    SRE_API Entity* createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize);
    SRE_API Entity* createGUIImageEntityFromAtlas(const std::string& fileName, const std::string& imageId);
    SRE_API Entity* createGUITextEntity(const std::string fontFile, uint32_t maxItems = 100u);

private:
    ScenesManager();

    void loadStartUpScene();
    void update(uint32_t elapsedTime);
    void onScenesLoaded();
    void removeDestroyedEntities();
    void destroyAllEntities();
    void release();

friend class RenderEngine;
friend class EditorSceneTree;
};

} // namespace

#endif
