#include "ScenesManager.h"
#include "Scene.h"
#include "GUIScene.h"
#include "SceneLoader.h"
#include "FileUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{

void ScenesManager::init()
{
    this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    this->editorScene.reset(new Scene{ "_editor_scene", "" });
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

Entity* ScenesManager::createEntityFromFile(std::string filePath, Entity* parent)
{
    Entity* result = this->scene->createEntityFromFile(filePath, parent);
	this->addToRenderer(result);
    return result;
}

Entity* ScenesManager::duplicateEntity(Entity* entity)
{
	Entity* result = this->scene->duplicateEntity(entity);
	this->addToRenderer(result);
	return result;
}

Entity* ScenesManager::getEntity(const std::string& name)
{
    Entity* result = this->scene->getEntity(name);

    if (result == nullptr)
        result = this->guiScene->getEntity(name);

    return result;
}

Entity* ScenesManager::createMeshEntity(Model* model, const char* meshName, Entity* parent)
{
    Entity* result = this->scene->createMeshEntity(model, meshName, parent);
    this->addToRenderer(result);
    return result;
}

Entity* ScenesManager::createPerspectiveCamera(float fov, float near, float far, Entity* parent)
{
    return this->scene->createPerspectiveCamera(fov, near, far, parent);
}

Entity* ScenesManager::createOrthoCamera(Entity* parent)
{
    return this->scene->createOrthoCamera(parent);
}

Entity* ScenesManager::createDirectionalLight(const std::string& name, Entity* parent)
{
	Entity* result = this->scene->createDirectionalLight(name, parent);
    this->addToRenderer(result);
    return result;
}

Entity* ScenesManager::createPointLight(const std::string& name, Entity* parent)
{
    Entity* result = this->scene->createPointLight(name, parent);
    this->addToRenderer(result);
    return result;
}

Entity* ScenesManager::createSkybox(const std::string& meshFilePath, const std::string& name, Entity* parent)
{
	Entity* result = this->scene->createSkybox(meshFilePath, name, parent);
	this->addToRenderer(result);
    return result;
}

Entity* ScenesManager::createGUIImageEntity(const std::string& filePath, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntity(filePath, name);
    this->addToRenderer(entity);
    return entity;
}

Entity* ScenesManager::createGUIImageEntity(const std::string& filePath, const glm::vec2& normalizedSize, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntity(filePath, normalizedSize, name);
    this->addToRenderer(entity);
    return entity;
}

Entity* ScenesManager::createGUIImageEntityFromAtlas(const std::string& filePath, const std::string& imageId, const std::string& name)
{
    Entity* entity = this->guiScene->createGUIImageEntityFromAtlas(filePath, imageId, name);
    this->addToRenderer(entity);
    return entity;
}

Entity* ScenesManager::createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems)
{
    Entity* entity = this->guiScene->createGUITextEntity(fontFile, name, maxItems);
    this->addToRenderer(entity);
    return entity;
}

Entity* ScenesManager::raycastFromScreen(const glm::vec2& mousePosition, const glm::vec2& viewportSize, Entity* selectedEntity)
{
	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	CameraComponent* camera = renderManager->getCurrentCamera();
	Ray ray = camera->getRayFromScreen(mousePosition, viewportSize);
	return this->raycast(ray, selectedEntity);
}

Entity* ScenesManager::raycast(const Ray& ray, Entity* selectedEntity)
{
    std::map<float, Entity*> foundEntities;
	this->scene->raycast(ray, foundEntities);

    Entity* result = nullptr;

    if (!foundEntities.empty())
    {
        auto it = foundEntities.begin();
        while (it != foundEntities.end())
        {
            Entity* entity = it->second;
            it++;

            if (entity == selectedEntity)
            {
                break;
            }
        }

        if (it != foundEntities.end())
        {
            result = it->second;
        }
        else
        {
            result = foundEntities.begin()->second;
        }
    }

    return result;
}

Scene* ScenesManager::getEditorScene()
{
    return this->editorScene.get();
}

void ScenesManager::addToRenderer(Entity* entity)
{
	this->renderManager->addEntity(entity);
}

void ScenesManager::setupEntityInitialPosition(Entity* entity)
{
    CameraComponent* camera = this->renderManager->getCurrentCamera();
    glm::vec3 cameraPosition = camera->getTransform()->getPosition();
    glm::vec3 forward = glm::normalize(camera->getTransform()->getForwardView());
    glm::vec3 entityPosition = cameraPosition + forward * 5.0f;
    entity->getTransform()->setPosition(entityPosition);
}

void ScenesManager::initEntities()
{
    this->scene->initEntities();
    this->guiScene->initEntities();
    this->editorScene->initEntities();
}

void ScenesManager::update(float elapsedTime)
{
    this->scene->update(elapsedTime);
    this->guiScene->update(elapsedTime);
    this->editorScene->update(elapsedTime);
}

void ScenesManager::loadScene(const char* scenePath)
{
	std::string sceneName = FileUtils::getFileName(scenePath);
    this->scene.reset(new Scene{ sceneName, scenePath });
    SceneLoader::load(this->scene.get());
    this->scene->onSceneLoaded();
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

    this->scene->onSceneSaved();
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

Entity* ScenesManager::createMeshEntity(const std::string& filePath, const char* meshName)
{
    Entity* entity = this->scene->createMeshEntity(filePath, meshName);
    this->addToRenderer(entity);

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
    this->scene.reset();
    this->guiScene.reset();
    this->editorScene.reset();

    EntityTypes::release();
    EntityComponentTypes::release();
}

} // namespace
