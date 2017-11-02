#include "GUIManager.h"
#include <engine/entities/components/gui/GUIImageComponent.h>

namespace sre
{

GUIManager::GUIManager() : AEntityManager() { }

Entity *GUIManager::createGUIImageEntity(const std::string &fileName)
{
	Entity *result = this->createEntity();
	GUIImageComponent *component = result->addComponent<GUIImageComponent>();
	component->load(fileName);
	return result;
}

Entity *GUIManager::createGUIImageEntityFromAtlas(const std::string &fileName, const std::string &imageId)
{
	Entity *result = this->createEntity();
	GUIImageComponent *component = result->addComponent<GUIImageComponent>();
	component->loadFromAtlas(fileName, imageId);
	return result;
}

Entity *GUIManager::createGUITextEntity(const std::string fontFile)
{
	Entity *result = this->createEntity();
	GUITextComponent *component = result->addComponent<GUITextComponent>(100);
	component->loadFont(fontFile);

	return result;
}

} // namespace
