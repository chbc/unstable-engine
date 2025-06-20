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

Entity* Scene::createPerspectiveCamera(float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::ASPECT_RATIO, near, far);

    return mainCamera;
}

Entity* Scene::createOrthoCamera(Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    return mainCamera;
}

Entity* Scene::createMeshEntity(const char* filePath, const char* meshName)
{
    Entity* entity = nullptr;
	std::string resultMeshName{ meshName };
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    Model* model = assetsManager->loadModel(filePath);

    if (model->getMeshCount() == 1)
    {
        entity = this->createEntity(resultMeshName.c_str());
        MeshComponent* meshComponent = entity->addComponent<MeshComponent>();
        meshComponent->load(model, resultMeshName.c_str());
    }
    else
    {
		entity = this->createEntity(FileUtils::getFileName(filePath));
		this->createMultiMeshEntity(entity, model);
    }

    return entity;
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

Entity* Scene::raycast(const Ray& ray, float maxDistance)
{
	Entity* result = nullptr;
	float minDistance = maxDistance;

	for (const auto& item : this->entities)
	{
		Entity* entity = item.second.get();
		if (entity->hasComponent<MeshComponent>())
		{
            ARenderableComponent* renderableComponent = entity->getComponent<MeshComponent>();
			TransformComponent* transform = entity->getTransform();
			Bounds bounds = renderableComponent->getBounds();

            const glm::mat4& modelMatrix = transform->getMatrix();
            float distance = 0;
			if (bounds.intersects(ray, modelMatrix, distance))
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
