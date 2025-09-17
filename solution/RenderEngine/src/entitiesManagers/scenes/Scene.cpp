#include "Scene.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "MeshComponent.h"
#include "AssetsManager.h"
#include "FileUtils.h"

namespace sre
{

Scene::Scene(std::string arg_name, std::string arg_filePath) : AScene(arg_name, arg_filePath) { }

Entity* Scene::createMeshEntity(const std::string& filePath, const char* meshName)
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    Model* model = assetsManager->loadModel(filePath);

    Entity* entity = this->createMeshEntity(model, meshName);
    return entity;
}

Entity* Scene::createMeshEntity(Model* model, const char* meshName, Entity* parent)
{
    Entity* result{ nullptr };
    if (model->getMeshCount() == 1)
    {
        std::string resultMeshName{ meshName };
        result = this->createEntity(resultMeshName.c_str(), parent);
        MeshComponent* meshComponent = result->addComponent<MeshComponent>();
        meshComponent->load(model, resultMeshName.c_str());
    }
    else
    {
        result = this->createEntity(FileUtils::getFileName(model->getFilePath()), parent);
        this->createMultiMeshEntity(result, model);
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

void Scene::createMultiMeshEntity(Entity* entity, Model* model)
{
	for (const auto& mesh : model->meshes)
	{
		std::string meshName = mesh.first;
		Entity* childEntity = this->createEntity(meshName, entity);
		MeshComponent* meshComponent = childEntity->addComponent<MeshComponent>();
		meshComponent->load(model, meshName.c_str());
	}
}

// light //
DirectionalLightComponent *Scene::createDirectionalLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "directional_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<DirectionalLightComponent>();
}

PointLightComponent *Scene::createPointLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "point_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<PointLightComponent>();
}

void Scene::onRefreshMeshes()
{
    AScene::onSceneLoaded();
}

Entity* Scene::raycast(const Ray& ray, Entity* parentEntity, float maxDistance)
{
	Entity* result = nullptr;
	float minDistance = maxDistance;

    if (parentEntity)
    {
        result = parentEntity->raycastChildren(ray, maxDistance);
    }
    
    if (!result)
    {
	    for (const auto& item : this->entities)
	    {
		    Entity* entity = item.second.get();
            float distance = 0;
            if (entity->raycast(ray, distance))
            {
                if (distance < minDistance)
                {
                    minDistance = distance;
                    result = entity;
                }
            }
	    }
    }

	return result;
}

} // namespace
