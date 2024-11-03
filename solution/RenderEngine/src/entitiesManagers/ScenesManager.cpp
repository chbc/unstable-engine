#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"

namespace sre
{

void ScenesManager::init()
{
    this->runtimeScene = UPTR<Scene>(new Scene{ "Runtime" });
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

void ScenesManager::loadScene(const char* fileName)
{
    // XXX
    Scene* scene = this->createScene(fileName);
    SceneLoader::load(scene, fileName);

    for (const auto& item : this->scenes)
        item->onSceneLoaded();

    this->guiScene->onSceneLoaded();
}

Scene* ScenesManager::getScene(const std::string& name)
{
    return this->scenes.front().get();
}

void ScenesManager::initEntities()
{
    for (const auto& item : this->scenes)
        item->initEntities();

    this->guiScene->initEntities();
}

void ScenesManager::update(float elapsedTime)
{
    this->runtimeScene->update(elapsedTime);

    for (const auto& item : this->scenes)
        item->update(elapsedTime);

    this->guiScene->update(elapsedTime);
}

void ScenesManager::removeDestroyedEntities()
{
    this->runtimeScene->removeDestroyedEntities();

    for (const auto& item : this->scenes)
        item->removeDestroyedEntities();

    this->guiScene->removeDestroyedEntities();
}

void ScenesManager::cleanUp()
{
    this->runtimeScene.reset(new Scene{"Runtime"});
    this->guiScene.reset(new GUIScene{});
    this->scenes.clear();
}

void ScenesManager::release()
{
    this->runtimeScene->release();

    for (const auto& item : this->scenes)
        item->release();

    this->guiScene->release();

    EntityComponentTypes::release();
}

} // namespace
