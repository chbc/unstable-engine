#include "AEntityManager.h"
#include <sstream>
#include <engine/systems/graphics/RenderManager.h>

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

	RenderManager::getInstance()->addEntity(entity);
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
