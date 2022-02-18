#include "AEntityManager.h"
#include <sstream>
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "CollectionsUtils.h"

namespace sre
{

AEntityManager::AEntityManager() : entityIndex(0), sceneLoaded(false) { }

Entity *AEntityManager::createEntity(const std::string& name, Entity* parent)
{
    Entity *result = new Entity;

    if (parent != nullptr)
        parent->addChild(result, name);
    else
    {
        std::string resultName = name;
        if (name.empty())
            resultName = Entity::generateEntityId(this->entityIndex);
        else if (this->entities.count(name) > 0)
            resultName = Entity::generateEntityId(this->entityIndex, name);

        result->name = resultName;
        this->entities[resultName] = UPTR<Entity>{ result };
    }

    return result;
}

Entity* AEntityManager::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
        result = this->entities[name].get();

    return result;
}

void AEntityManager::update(uint32_t elapsedTime)
{
    for (const auto& item : this->entities)
    {
        item.second->onUpdate(elapsedTime);
    }
}

void AEntityManager::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
}

void AEntityManager::onSceneLoaded()
{
    RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();

    for (const auto &item : this->entities)
    {
        renderManager->addEntity(item.second.get());
        item.second->onStart();
    }

    this->sceneLoaded = true;
}

void AEntityManager::destroyAllEntities()
{
    for (auto& item : this->entities)
        item.second->destroy();
}

void AEntityManager::release()
{
    this->entities.clear();
}

} // namespace
