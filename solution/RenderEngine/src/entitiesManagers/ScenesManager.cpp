#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"
#include "FileUtils.h"

namespace sre
{

std::string ScenesManager::getMainSceneName()
{
    std::string result = (this->scene != nullptr) ? this->scene->name : "";
    return result;
}

Entity* ScenesManager::createEntity(std::string name, Entity* parent)
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

Entity* ScenesManager::createGUIImageEntity(const std::string& fileName, const std::string& name)
{
    return this->guiScene->createGUIImageEntity(fileName, name);
}

Entity* ScenesManager::createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize, const std::string& name)
{
    return this->guiScene->createGUIImageEntity(fileName, normalizedSize, name);
}

Entity* ScenesManager::createGUIImageEntityFromAtlas(const std::string& fileName, const std::string& imageId, const std::string& name)
{
    return this->guiScene->createGUIImageEntityFromAtlas(fileName, imageId, name);
}

Entity* ScenesManager::createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems)
{
    return this->guiScene->createGUITextEntity(fontFile, name, maxItems);
}

void ScenesManager::loadScene(const char* scenePath)
{
	std::string sceneName = FileUtils::getFileName(scenePath);
    this->scene.reset(new Scene{ sceneName });
    SceneLoader::load(this->scene.get(), scenePath);
    this->scene->onSceneLoaded();
}

void ScenesManager::loadGuiScene(const char* scenePath)
{
    std::string sceneName = FileUtils::getFileName(scenePath);
    this->guiScene.reset(new GUIScene{ sceneName });
    SceneLoader::load(this->guiScene.get(), scenePath);
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
    this->guiScene.reset();
}

void ScenesManager::preRelease()
{
    this->scene.reset();
    this->guiScene.reset();

    EntityTypes::release();
    EntityComponentTypes::release();
}

} // namespace
