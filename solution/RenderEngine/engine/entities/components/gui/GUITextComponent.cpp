#include "GUITextComponent.h"

#include <engine/systems/multimedia/textures/AtlasManager.h>
#include <engine/systems/multimedia/textures/Texture.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity) : AEntityComponent(entity)
{ }

void GUITextComponent::loadFont(const std::string &fontFile)
{
	AtlasManager *atlasManager = AtlasManager::getInstance();
	this->atlas = atlasManager->getAtlas(fontFile);
}

void GUITextComponent::setText(const std::string &text)
{

}

} // namespace
