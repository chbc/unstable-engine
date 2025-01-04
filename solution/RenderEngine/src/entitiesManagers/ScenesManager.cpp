#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"

namespace sre
{

void ScenesManager::init()
{
    this->guiScene = UPTR<GUIScene>(new GUIScene{});
}

Scene* ScenesManager::createScene(const std::string& name)
{
    this->scene.reset(new Scene{ name });
    return this->scene.get();
}

std::string ScenesManager::getMainSceneName()
{
    std::string result = (this->scene != nullptr) ? this->scene->name : "";
    return result;
}

Entity* ScenesManager::createEntity(const std::string& name, Entity* parent)
{
    return this->scene->createEntity(name, parent);
}

Entity* ScenesManager::getEntity(const std::string& name)
{
    Entity* result = this->scene->getEntity(name);

    if (result == nullptr)
        result = this->guiScene->getEntity(name);

    return result;
}

Entity* ScenesManager::createPerspectiveCamera(float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    return this->scene->createPerspectiveCamera(fov, near, far, parent, isMainCamera);
}

Entity* ScenesManager::createOrthoCamera(Entity* parent, bool isMainCamera)
{
    return this->scene->createOrthoCamera(parent, isMainCamera);
}

DirectionalLightComponent* ScenesManager::createDirectionalLight(const std::string& name, Entity* parent)
{
    return this->scene->createDirectionalLight(name, parent);
}

PointLightComponent* ScenesManager::createPointLight(const std::string& name, Entity* parent)
{
    return this->scene->createPointLight(name, parent);
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

void ScenesManager::loadScene(const char* sceneName)
{
    Scene* scene = this->createScene(sceneName);
    SceneLoader::load(scene, sceneName);

    this->scene->onSceneLoaded();
    this->guiScene->onSceneLoaded();
}

void ScenesManager::saveScenes()
{
    SceneLoader::save(this->scene.get(), this->scene->name.c_str());
    SceneLoader::save(this->guiScene.get(), this->guiScene->name.c_str());
}

void ScenesManager::initEntities()
{
    this->scene->initEntities();
    this->guiScene->initEntities();
}

void ScenesManager::update(float elapsedTime)
{
    this->scene->update(elapsedTime);
    this->guiScene->update(elapsedTime);
}

Entity* ScenesManager::createMeshEntity(const char* name, const char* fileName)
{
    return this->scene->createMeshEntity(name, fileName);
}

void ScenesManager::removeDestroyedEntities()
{
    this->scene->removeDestroyedEntities();
    this->guiScene->removeDestroyedEntities();
}

void ScenesManager::cleanUp()
{
    this->scene.reset();
    this->guiScene.reset(new GUIScene);
}

void ScenesManager::preRelease()
{
    this->scene.reset();
    this->guiScene.reset();

    EntityComponentTypes::release();
}

} // namespace
