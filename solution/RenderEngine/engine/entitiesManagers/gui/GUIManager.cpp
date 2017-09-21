#include "GUIManager.h"
#include <engine/entities/components/gui/GUIImageComponent.h>

namespace sre
{

GUIManager::GUIManager() : AEntityManager() { }

Entity *GUIManager::createGUIImageEntity(const std::string &fileName)
{
	Entity *result = this->createEntity();
	result->addComponent<GUIImageComponent>(fileName);
	return result;
}

Entity *GUIManager::createGUITextEntity(const std::string fontFile)
{
	Entity *result = this->createEntity();
	GUITextComponent *component = result->addComponent<GUITextComponent>();
	component->loadFont(fontFile);

	return result;
}

} // namespace
