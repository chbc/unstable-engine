#include "Scene.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
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

Entity* Scene::createMeshEntity(const char* entityName, const char* filePath, const char* meshName)
{
    Entity* entity = nullptr;
	std::string resultMeshName{ meshName };
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    Model* model = assetsManager->loadModel(filePath);

    if ((resultMeshName == "") && (model->getMeshCount() == 1))
    {
		resultMeshName = model->meshes.begin()->first;
    }

    if (resultMeshName != "")
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

    this->renderManager->addEntity(entity);

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

} // namespace
