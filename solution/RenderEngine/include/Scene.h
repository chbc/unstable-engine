#pragma once

#include "AScene.h"
#include "CameraComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"

namespace sre
{

class Scene : public AScene
{
private:
    Scene(std::string arg_name, std::string arg_filePath);

private:
    Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr, bool isMainCamera = true);
    Entity* createOrthoCamera(Entity* parent = nullptr, bool isMainCamera = true);

    // renderables //
    Entity* createMeshEntity(const char* entityName, const char* filePath, const char* meshName);

    // light //
    DirectionalLightComponent* createDirectionalLight(const std::string& entityName = "", Entity* parent = nullptr);
    PointLightComponent* createPointLight(const std::string& entityName = "", Entity* parent = nullptr);

friend class ScenesManager;
friend class SceneLoader;
};

} // namespace
