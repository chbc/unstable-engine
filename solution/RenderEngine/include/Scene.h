#pragma once

#include "AScene.h"
#include "CameraComponent.h"
#include "Ray.h"

namespace sre
{

struct Model;
class ABaseMaterial;
class DirectionalLightComponent;
class PointLightComponent;
class SkyboxComponent;

class Scene : public AScene
{
private:
    const char* DEFAULT_MATERIAL_PATH = "engine/media/materials/DefaultMaterial.mat";
	const char* SKYBOX_MATERIAL_PATH = "engine/media/materials/IndustrialSunsetSkybox.mat";

private:
    Scene(std::string arg_name, std::string arg_filePath);

private:
    Entity* createMeshEntity(const std::string& filePath, const char* meshName);
    Entity* createMeshEntity(Model* model, ABaseMaterial* material, const char* meshName, Entity* parent = nullptr);
    Entity* createPerspectiveCamera(float fov = 70.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr);
    Entity* createOrthoCamera(Entity* parent = nullptr);
    Entity* createSkybox(const std::string& meshFilePath, const std::string& entityName = "", Entity* parent = nullptr);
    void createMultiMeshEntity(Entity* entity, Model* model, ABaseMaterial* material);
    DirectionalLightComponent* createDirectionalLight(const std::string& entityName = "", Entity* parent = nullptr);
    PointLightComponent* createPointLight(const std::string& entityName = "", Entity* parent = nullptr);

    void onRefreshMeshes();

	Entity* raycast(const Ray& ray, Entity* parentEntity, float maxDistance);

friend class ScenesManager;
friend class SceneLoader;
friend class SceneViewportCamera;
};

} // namespace
