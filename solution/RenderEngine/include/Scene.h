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
    Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    Entity* createOrthoCamera(Entity* parent = nullptr, bool isMainCamera = true);

    // renderables //
    Entity* createMeshEntity(const char* name, const char* fileName);

    // light //
    DirectionalLightComponent* createDirectionalLight(const std::string& name = "", Entity* parent = nullptr);
    PointLightComponent* createPointLight(const std::string& name = "", Entity* parent = nullptr);

friend class ScenesManager;
friend class SceneLoader;
};

} // namespace
