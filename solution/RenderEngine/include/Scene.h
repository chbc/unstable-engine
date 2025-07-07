#pragma once

#include "AScene.h"
#include "CameraComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "Ray.h"

namespace sre
{

struct Model;

class Scene : public AScene
{
private:
    Scene(std::string arg_name, std::string arg_filePath);

private:
    Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr);
    Entity* createOrthoCamera(Entity* parent = nullptr);

    // renderables //
    Entity* createMeshEntity(const char* filePath, const char* meshName);
    void createMultiMeshEntity(Entity* entity, Model* model);

    // light //
    DirectionalLightComponent* createDirectionalLight(const std::string& entityName = "", Entity* parent = nullptr);
    PointLightComponent* createPointLight(const std::string& entityName = "", Entity* parent = nullptr);

    void onRefreshMeshes();

	Entity* raycast(const Ray& ray, float maxDistance);

friend class ScenesManager;
friend class SceneLoader;
friend class SceneViewportCamera;
};

} // namespace
