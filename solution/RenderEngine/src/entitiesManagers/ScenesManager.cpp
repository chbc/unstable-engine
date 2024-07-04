#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"

namespace sre
{

ScenesManager::ScenesManager()
{
    this->runtimeScene = UPTR<Scene>(new Scene{ "runtimeScene" });
    this->guiScene = UPTR<GUIScene>(new GUIScene{});
}

Scene* ScenesManager::createScene(const std::string& name)
{
    Scene* result = new Scene{ name };
    this->scenes.emplace_back(result);

    return result;
}

Entity* ScenesManager::createEntity(const std::string& name, Entity* parent)
{
    return this->runtimeScene->createEntity(name, parent);
}

Entity* ScenesManager::getEntity(const std::string& name)
{
    Entity* result = this->runtimeScene->getEntity(name);
    if (result == nullptr)
    {
        for (const auto& item : this->scenes)
        {
            result = item->getEntity(name);
            if (result != nullptr)
                break;
        }
    }

    if (result == nullptr)
        result = this->guiScene->getEntity(name);

    return result;
}

Entity* ScenesManager::createPerspectiveCamera(float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    return this->runtimeScene->createPerspectiveCamera(fov, near, far, parent, isMainCamera);
}

Entity* ScenesManager::createOrthoCamera(Entity* parent, bool isMainCamera)
{
    return this->runtimeScene->createOrthoCamera(parent, isMainCamera);
}

Entity* ScenesManager::createPlaneEntity(const glm::vec2& size, float tileMultiplier, const std::string& name, Entity* parent)
{
    return this->runtimeScene->createPlaneEntity(size, tileMultiplier, name, parent);
}

Entity* ScenesManager::createCubeEntity(float size, const std::string& name, Entity* parent)
{
    return this->runtimeScene->createCubeEntity(size, name, parent);
}

Entity* ScenesManager::createModelEntity(const std::string& fileName, const std::string& name, Entity* parent)
{
    return this->runtimeScene->createModelEntity(fileName, name, parent);
}

DirectionalLightComponent* ScenesManager::createDirectionalLight(const std::string& name, Entity* parent)
{
    return this->runtimeScene->createDirectionalLight(name, parent);
}

PointLightComponent* ScenesManager::createPointLight(const std::string& name, Entity* parent)
{
    return this->runtimeScene->createPointLight(name, parent);
}

CameraComponent* ScenesManager::getMainCamera()
{
    return this->runtimeScene->getMainCamera();
}

Entity* ScenesManager::createMeshEntity(MeshData* objectData, const std::string& name, Entity* parent)
{
    return this->runtimeScene->createMeshEntity(objectData, name, parent);
}

void ScenesManager::setMainCamera(CameraComponent* camera)
{
    this->runtimeScene->setMainCamera(camera);
}

Entity* ScenesManager::createGUIImageEntity(const std::string& fileName)
{
    return this->guiScene->createGUIImageEntity(fileName);
}

Entity* ScenesManager::createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize)
{
    return this->guiScene->createGUIImageEntity(fileName, normalizedSize);
}

Entity* ScenesManager::createGUIImageEntityFromAtlas(const std::string& fileName, const std::string& imageId)
{
    return this->guiScene->createGUIImageEntityFromAtlas(fileName, imageId);
}

Entity* ScenesManager::createGUITextEntity(const std::string fontFile, uint32_t maxItems)
{
    return this->guiScene->createGUITextEntity(fontFile, maxItems);
}

void ScenesManager::loadStartUpScene()
{
    /*
    SceneLoader::load(this->runtimeScene.get());
    for (const auto& item : this->scenes)
        SceneLoader::load(item.get());
    */

    this->onScenesLoaded();
}

void ScenesManager::update(uint32_t elapsedTime)
{
    this->runtimeScene->update(elapsedTime);

    for (const auto& item : this->scenes)
        item->update(elapsedTime);

    this->guiScene->update(elapsedTime);
}

void ScenesManager::onScenesLoaded()
{
    this->runtimeScene->onSceneLoaded();

    for (const auto& item : this->scenes)
        item->onSceneLoaded();

    this->guiScene->onSceneLoaded();
}

void ScenesManager::removeDestroyedEntities()
{
    this->runtimeScene->removeDestroyedEntities();

    for (const auto& item : this->scenes)
        item->removeDestroyedEntities();

    this->guiScene->removeDestroyedEntities();
}

void ScenesManager::destroyAllEntities()
{
    this->runtimeScene->destroyAllEntities();

    for (const auto& item : this->scenes)
        item->destroyAllEntities();

    this->guiScene->destroyAllEntities();
}

void ScenesManager::release()
{
    this->runtimeScene->release();

    for (const auto& item : this->scenes)
        item->release();

    this->guiScene->release();
}

} // namespace
