#include "GUITextComponent.h"

#include <engine/systems/multimedia/textures/AtlasManager.h>
#include <engine/systems/multimedia/textures/Texture.h>
#include <engine/utils/math/Rect.h>
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

void GUITextComponent::makeGliph(char id)
{

	const Rect *uv = this->atlas->getItem(id);

	float x1 = uv->topLeft.x;
	float y1 = uv->topLeft.y;
	float x2 = uv->topLeft.x + uv->size.x;
	float y2 = uv->topLeft.y + uv->size.y;

	float planeTexCoords[] = 
	{
		x1, y1,
		x1, y2,
		x2, y2,
		x2, y1
	};

	this->meshData = PrimitiveMeshFactory::createPlane2D(1.0f, 1.0f, planeTexCoords);
}

uint32_t GUITextComponent::getTextureId()
{
	return this->atlas->getTextureId();
}

} // namespace
