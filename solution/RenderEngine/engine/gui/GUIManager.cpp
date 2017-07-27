#include "GUIManager.h"
#include <engine/entities/components/gui/GUIImageComponent.h>
#include <engine/systems/graphics/RenderManager.h>
#include <sstream>

namespace sre
{

GUIManager::GUIManager() : EntityIndex(0) { }

GUIManager::~GUIManager()
{
	this->entities.clear();
}

Entity *GUIManager::createGUIImageEntity(const std::string &fileName)
{
	Entity *entity = new Entity;
	entity->addComponent<GUIImageComponent>(fileName);

	return entity;
}

Entity *GUIManager::createGUITextEntity(const std::string fontFile)
{
	Entity *entity = new Entity;
	GUITextComponent *component = entity->addComponent<GUITextComponent>();
	component->loadFont(fontFile);

	return entity;
}

void GUIManager::addEntity(Entity *entity, const std::string &name)
{
	std::string resultName = name;
	if (name.size() == 0)
	{
		resultName = this->generateEntityId();
	}

	this->entities[resultName] = UPTR<Entity>{ entity };
	RenderManager::getInstance()->addEntity(entity);
}

const std::string GUIManager::generateEntityId()
{
	std::string result;
	
	std::stringstream stream;
	stream << "entity_" << EntityIndex;
	result = stream.str();
	EntityIndex++;

	return result;
}

} // namespace
