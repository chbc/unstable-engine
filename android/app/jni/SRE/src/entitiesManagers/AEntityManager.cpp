#include "AEntityManager.h"
#include <sstream>
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "CollectionsUtils.h"

namespace sre
{

AEntityManager::AEntityManager() : entityIndex(0), sceneLoaded(false) { }

AEntityManager::~AEntityManager()
{
    this->entities.clear();
    this->entitiesToBeAdded.clear();
}

Entity *AEntityManager::createEntity()
{
    Entity *result = new Entity;
    this->entitiesToBeAdded[result] = UPTR<Entity>{ result };

    return result;
}

void AEntityManager::addEntity(Entity *entity, const std::string &name)
{
    std::string resultName = name;
    if (name.empty())
    {
        resultName = Entity::generateEntityId(this->entityIndex);
    }
    else if (this->entities.count(name) > 0)
    {
        resultName = Entity::generateEntityId(this->entityIndex, name);
    }

    entity->name = resultName;
    this->entities[resultName] = std::move(this->entitiesToBeAdded[entity]);
    this->entitiesToBeAdded.erase(entity);
	
    if (this->sceneLoaded)
    {
        SingletonsManager::getInstance()->resolve<RenderManager>()->addEntity(entity);
        entity->onStart();
    }
}

Entity* AEntityManager::getEntity(const std::string& name)
{
    Entity* result = nullptr;
    if (this->entities.count(name) > 0)
        result = this->entities[name].get();

    return result;
}

void AEntityManager::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->entities);
    CollectionsUtils::removeIfEntityIsDestroyed(this->entitiesToBeAdded);
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

    for (auto& item : this->entitiesToBeAdded)
        item.second->destroy();
}

} // namespace
