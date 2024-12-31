#include "AScene.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{
uint32_t AScene::EntityIndex = 0;

AScene::AScene(std::string arg_name) : name(arg_name), sceneLoaded(false) { }

Entity* AScene::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
        result = this->entities[name].get();
    else if (this->entityAssets.count(name) > 0)
        result = this->entityAssets[name];

    return result;
}

Entity* AScene::createEntity(const std::string& name, Entity* parent)
{
    Entity* result = nullptr;

    if (parent != nullptr)
        result = parent->createChild(name);
    else
    {
        std::string resultName = name;
        if (name.empty())
            resultName = Entity::generateEntityId(EntityIndex);
        else if (this->entities.count(name) > 0)
            resultName = Entity::generateEntityId(EntityIndex, name);

        result = new Entity{ resultName };
        this->entities[resultName] = UPTR<Entity>{ result };
    }

    return result;
}

void AScene::addEntityAsset(Entity* entityAsset)
{
    this->entityAssets.emplace(entityAsset->getName(), entityAsset);
}

void AScene::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
    CollectionsUtils::removeIfEntityIsDestroyed(this->entityAssets);
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

void AScene::clean()
{
    this->entities.clear();
    this->entityAssets.clear();
}

void AScene::release()
{
    this->entities.clear();
    this->entityAssets.clear();
}

} // namespace
