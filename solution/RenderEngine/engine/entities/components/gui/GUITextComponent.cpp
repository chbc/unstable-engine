#include "GUITextComponent.h"

#include <engine/systems/multimedia/textures/AtlasManager.h>
#include <engine/systems/multimedia/textures/Texture.h>
#include <engine/systems/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

GUITextComponent::GUITextComponent(Entity *entity) : GUIImageComponent(entity)
{ }

void GUITextComponent::loadFont(const std::string &fontFile)
{
	AtlasManager *atlasManager = AtlasManager::getInstance();
	this->atlas = atlasManager->getFont(fontFile);
	this->makeGliph('H'); // ###
}

void GUITextComponent::setText(const std::string &text)
{

}

void GUITextComponent::makeGliph(int id)
{
	const Rect uv = this->atlas->getItem(std::to_string(id));
	this->meshData = PrimitiveMeshFactory::createPlane2D(1.0f, 1.0f, uv);
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
