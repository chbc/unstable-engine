#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "AssetsManager.h"
#include "FileUtils.h"

namespace sre
{
uint32_t AScene::EntityIndex = 0;

AScene::AScene(std::string arg_name) : name(arg_name), sceneLoaded(false) { }

AScene::~AScene()
{
    this->entities.clear();

    if (!this->entityAssets.empty())
    {
        AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
        auto& it = this->entityAssets.begin();
        for (it; it != this->entityAssets.end();)
        {
            assetsManager->releaseEntity((*it).second);
            it = this->entityAssets.erase(it);
        }
    }
}

Entity* AScene::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
        result = this->entities[name].get();
    else if (this->entityAssets.count(name) > 0)
        result = this->entityAssets[name];

    return result;
}

Entity* AScene::createEntity(std::string name, Entity* parent, const char* className)
{
    Entity* result = nullptr;

    if (parent != nullptr)
        result = parent->createChild(name, className);
    else
    {
        this->resolveName(name);
        result = Entity::Create(name, className);
        this->entities[name] = UPTR<Entity>{ result };
    }

    return result;
}

Entity* AScene::spawnEntity(const char* entityFile, const glm::vec3& position)
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    std::string name = FileUtils::getFileName(entityFile);
    Entity* entity = assetsManager->loadEntity(entityFile, name);
    this->addEntityAsset(entity);

    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    renderManager->addEntity(entity);

    entity->getTransform()->setPosition(position);

    return entity;
}

void AScene::addEntityAsset(Entity* entityAsset)
{
    resolveName(entityAsset->name);
    this->entityAssets.emplace(entityAsset->getName(), entityAsset);
}

void AScene::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);

    auto& it = this->entityAssets.begin();
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();

    for (it; it != this->entityAssets.end();)
    {
        if (!(*it).second->isAlive())
        {
            assetsManager->releaseEntity((*it).second);
            it = this->entityAssets.erase(it);
        }
        else
            ++it;
    }
}

void AScene::initEntities()
{
    for (const auto& item : this->entities)
    {
        item.second->onInit();
    }

    for (const auto& item : this->entityAssets)
    {
        item.second->onInit();
    }
}

void AScene::update(float elapsedTime)
{
    for (const auto& item : this->entities)
    {
        item.second->onUpdate(elapsedTime);
    }

    for (const auto& item : this->entityAssets)
    {
        item.second->onUpdate(elapsedTime);
    }
}

void AScene::onSceneLoaded()
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();

    for (const auto& item : this->entities)
    {
        renderManager->addEntity(item.second.get());
    }

    for (const auto& item : this->entityAssets)
    {
        renderManager->addEntity(item.second);
    }

    this->sceneLoaded = true;
}

void AScene::resolveName(std::string& name)
{
    if (name.empty())
    {
        name = Entity::generateEntityId(EntityIndex);
    }
    else if ((this->entities.count(name) > 0) || (this->entityAssets.count(name) > 0))
    {
        name = Entity::generateEntityId(EntityIndex, name);
    }
}

} // namespace
