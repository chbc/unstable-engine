#pragma once

#include "AScene.h"
#include "CameraComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

class Scene : public AScene
{
private:
    class RenderManager* renderManager;

private:
    Scene(std::string name);

private:
    Entity* createPerspectiveCamera(uint32_t& index, float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    Entity* createOrthoCamera(uint32_t& index, Entity* parent = nullptr, bool isMainCamera = true);

    // renderables //
    Entity* createPlaneEntity(uint32_t& index, const glm::vec2& size, float tileMultiplier = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    Entity *createCubeEntity(uint32_t& index, float size = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    Entity *createModelEntity(uint32_t& index, const std::string &fileName, const std::string& name = "", Entity* parent = nullptr);

    // light //
    DirectionalLightComponent* createDirectionalLight(uint32_t& index, const std::string& name = "", Entity* parent = nullptr);
    PointLightComponent* createPointLight(uint32_t& index, const std::string& name = "", Entity* parent = nullptr);

    // camera //
    class CameraComponent *getMainCamera();
    Entity *createMeshEntity(uint32_t& index, MeshData* objectData, const std::string& name = "", Entity* parent = nullptr);
    void setMainCamera(CameraComponent* camera);

friend class ScenesManager;
};

} // namespace
