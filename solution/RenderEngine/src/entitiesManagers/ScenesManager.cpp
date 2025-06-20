#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"
#include "FileUtils.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "RenderManager.h"

namespace sre
{

void ScenesManager::init()
{
    this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();

    Action* action = new Action{ [&](void* message) { this->onRefreshMeshes(); } };
    this->refreshMeshesAction = SPTR<Action>(action);
}

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

Entity* ScenesManager::createGUIImageEntity(const std::string& filePath, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntity(filePath, name);
    this->renderManager->addEntity(entity);
    return entity;
}

Entity* ScenesManager::createGUIImageEntity(const std::string& filePath, const glm::vec2& normalizedSize, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntity(filePath, normalizedSize, name);
    this->renderManager->addEntity(entity);
    return entity;
}

Entity* ScenesManager::createGUIImageEntityFromAtlas(const std::string& filePath, const std::string& imageId, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntityFromAtlas(filePath, imageId, name);
    this->renderManager->addEntity(entity);
    return entity;
}

Entity* ScenesManager::createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems)
{
    Entity* entity = this->guiScene->createGUITextEntity(fontFile, name, maxItems);
    this->renderManager->addEntity(entity);
    return entity;
}

Entity* ScenesManager::raycast(const Ray& ray, float maxDistance)
{
	return this->scene->raycast(ray, maxDistance);
}

Entity* ScenesManager::raycastFromScreen(const glm::vec2& mousePosition, const glm::vec2& viewportSize, float maxDistance)
{
	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	CameraComponent* camera = renderManager->getCurrentCamera();
	Ray ray = camera->getRayFromScreen(mousePosition, viewportSize);
	return this->raycast(ray, maxDistance);
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

void ScenesManager::loadScene(const char* scenePath)
{
    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->removeListener<RefreshMeshesMessage>(this->refreshMeshesAction.get());

	std::string sceneName = FileUtils::getFileName(scenePath);
    this->scene.reset(new Scene{ sceneName, scenePath });
    SceneLoader::load(this->scene.get());
    this->scene->onSceneLoaded();

    messagesManager->addListener<RefreshMeshesMessage>(this->refreshMeshesAction.get());
}

void ScenesManager::loadGuiScene(const char* scenePath)
{
    std::string sceneName = FileUtils::getFileName(scenePath);
    this->guiScene.reset(new GUIScene{ sceneName, scenePath });
    SceneLoader::load(this->guiScene.get());
    this->guiScene->onSceneLoaded();
}

void ScenesManager::saveScene(std::string scenePath)
{
    if (!scenePath.empty())
    {
        this->scene->filePath = scenePath;
        this->scene->name = FileUtils::getFileName(scenePath);
    }
    SceneLoader::save(this->scene.get());
}

void ScenesManager::saveGuiScene(std::string scenePath)
{
    if (!scenePath.empty())
    {
        this->guiScene->filePath = scenePath;
        this->guiScene->name = FileUtils::getFileName(scenePath);
    }
    SceneLoader::save(this->guiScene.get());
}

bool ScenesManager::isSceneStored()
{
    return this->isBaseSceneStored(this->scene.get());
}

bool ScenesManager::isGuiSceneStored()
{
    return this->isBaseSceneStored(this->guiScene.get());
}

bool ScenesManager::isBaseSceneStored(AScene* baseScene)
{
    bool exists = FileUtils::fileExists(baseScene->filePath);
    bool result = exists && FileUtils::isPathFromGameContent(baseScene->filePath);

    return result;
}

Entity* ScenesManager::createMeshEntity(const char* filePath, const char* meshName)
{
    Entity* entity = this->scene->createMeshEntity(filePath, meshName);
    this->renderManager->addEntity(entity);

    return entity;
}

AScene* ScenesManager::getScene()
{
    return this->scene.get();
}

AScene* ScenesManager::getGuiScene()
{
    return this->guiScene.get();
}

void ScenesManager::onRefreshMeshes()
{
    this->renderManager->cleanUpMeshes();
    this->scene->onRefreshMeshes();
}

void ScenesManager::removeDestroyedEntities()
{
    if (this->scene)
    {
        this->scene->removeDestroyedEntities();
    }

    if (guiScene)
    {
        this->guiScene->removeDestroyedEntities();
    }
}

void ScenesManager::preRelease()
{
    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->removeListener<RefreshMeshesMessage>(this->refreshMeshesAction.get());

    this->scene.reset();
    this->guiScene.reset();

    EntityTypes::release();
    EntityComponentTypes::release();
}

} // namespace
