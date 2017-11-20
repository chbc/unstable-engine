#include "AEntityManager.h"
#include <sstream>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

AEntityManager::AEntityManager() : entityIndex(0) { }

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

	SingletonsManager::getInstance()->resolve<RenderManager>()->addEntity(entity);
    entity->onStart();
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

} // namespace
