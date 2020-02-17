#include "AEntityManager.h"
#include <sstream>
#include "SingletonsManager.h"
#include "RenderManager.h"

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
    if (name.size() == 0)
    {
        resultName = this->generateEntityId();
    }

    this->entities[resultName] = std::move(this->entitiesToBeAdded[entity]);
    this->entitiesToBeAdded.erase(entity);

    if (this->sceneLoaded)
    {
        SingletonsManager::getInstance()->resolve<RenderManager>()->addEntity(entity);
        entity->onStart();
    }
}

const std::string AEntityManager::generateEntityId()
{
    std::string result;

    std::stringstream stream;
    stream << "entity_" << entityIndex;
    result = stream.str();
    this->entityIndex++;

    return result;
}

void AEntityManager::removeDestroyedEntities()
{
	/* ###
    std::experimental::erase_if(this->entities, [](const auto &item) { return !item.second->isAlive(); });
	*/
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

} // namespace
