#include "Scene.h"

#include "CameraComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SkyboxComponent.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "MeshComponent.h"
#include "AssetsManager.h"
#include "FileUtils.h"

#include <map>

namespace sre
{

Scene::Scene(std::string arg_name, std::string arg_filePath) : AScene(arg_name, arg_filePath) { }

Entity* Scene::createMeshEntity(const std::string& filePath, const char* meshName)
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    Model* model = assetsManager->loadModel(filePath);
	ABaseMaterial* material = assetsManager->loadMaterial(this->DEFAULT_MATERIAL_PATH);

    Entity* entity = this->createMeshEntity(model, material, meshName, nullptr);
    return entity;
}

Entity* Scene::createMeshEntity(Model* model, const char* meshName, Entity* parent)
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    ABaseMaterial* material = assetsManager->loadMaterial(this->DEFAULT_MATERIAL_PATH);
	
    Entity* result = this->createMeshEntity(model, material, meshName, parent);
    return result;
}

Entity* Scene::createMeshEntity(Model* model, ABaseMaterial* material, const char* meshName, Entity* parent)
{
    Entity* result{ nullptr };
    if (model->getMeshCount() == 1)
    {
        std::string resultMeshName{ meshName };
        result = this->createEntity(resultMeshName.c_str(), parent);
        MeshComponent* meshComponent = result->addComponent<MeshComponent>();
        meshComponent->load(model, material, resultMeshName.c_str());
    }
    else
    {
        result = this->createEntity(FileUtils::getFileName(model->getFilePath()), parent);
        this->createMultiMeshEntity(result, model, material);
    }

    return result;
}

Entity* Scene::createPerspectiveCamera(float fov, float near, float far, Entity* parent)
{
    Entity* result = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = result->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::ASPECT_RATIO, near, far);

    return result;
}

Entity* Scene::createOrthoCamera(Entity* parent)
{
    Entity* result = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = result->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    return result;
}

Entity* Scene::createSkybox(const std::string& meshFilePath, const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "skybox" : entityName;
    Entity* result = this->createEntity(resultName, parent);

    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    Model* model = assetsManager->loadModel(meshFilePath);
	ABaseMaterial* material = assetsManager->loadMaterial(this->SKYBOX_MATERIAL_PATH);

	SkyboxComponent* skyboxComponent = result->addComponent<SkyboxComponent>();
	skyboxComponent->load(model, material, resultName.c_str());

    return result;
}

void Scene::createMultiMeshEntity(Entity* entity, Model* model, ABaseMaterial* material)
{
	for (const auto& mesh : model->meshes)
	{
		std::string meshName = mesh.first;
		Entity* childEntity = this->createEntity(meshName, entity);
		MeshComponent* meshComponent = childEntity->addComponent<MeshComponent>();
		meshComponent->load(model, material, meshName.c_str());
	}
}

// light //
Entity*Scene::createDirectionalLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "directional_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);
    newEntity->addComponent<DirectionalLightComponent>();

    return newEntity;
}

Entity*Scene::createPointLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "point_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);
    newEntity->addComponent<PointLightComponent>();

    return newEntity;
}

void Scene::raycast(const Ray& ray, std::map<float, Entity*>& result)
{
    std::map<float, Entity*> foundEntities;
    
	for (const auto& item : this->entities)
	{
		Entity* entity = item.second.get();
        float distance = 0;
        if (entity->raycast(ray, distance))
        {
            result[distance] = entity;
        }

        entity->raycastChildren(ray, result);
	}
}

} // namespace
