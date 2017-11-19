#include "GUIImageComponent.h"
#include <engine/core/graphics/RenderManager.h>
#include <engine/core/multimedia/MultimediaManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/multimedia/textures/Texture.h>
#include <engine/core/multimedia/textures/atlases/AtlasManager.h>
#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

GUIImageComponent::GUIImageComponent(Entity *entity, uint32_t maxItems) 
    :   AEntityComponent(entity), 
        maxItems(maxItems), isDynamic(maxItems > 0)
{
	this->setUIPosition(glm::vec2(0.0f, 0.0f));
}

void GUIImageComponent::load(const std::string &fileName)
{
	Texture *texture = RenderManager::getInstance()->loadGUITexture(fileName);
	glm::vec2 pixelSize(texture->getWidth(), texture->getHeight());
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(pixelSize);

	this->meshData = (PrimitiveMeshFactory()).createPlane2D(screenBasedSize);
	this->textureId = texture->getId();
}

void GUIImageComponent::loadFromAtlas(const std::string &fileName, const std::string &imageId)
{
	Atlas *atlas = SingletonsManager::getInstance()->resolve<AtlasManager>()->getAtlas(fileName);

	const AtlasItem *atlasItem = atlas->getItem(imageId);

	this->meshData = (PrimitiveMeshFactory()).createPlane2D(atlasItem->normalizedSize, atlasItem->uv);
	this->textureId = atlas->getTextureId();
}

void GUIImageComponent::setUIPosition(const glm::vec2 &position)
{
	glm::vec3 realPosition = glm::vec3
	(
		((position.x * 2) - 1), 
		-(position.y * 2) + 1, 
		0.0f
	);
	this->getTransform()->setPosition(realPosition);

	this->uiPosition = position;
}

glm::vec2 GUIImageComponent::getUIPosition()
{
	return this->uiPosition;
}

uint32_t GUIImageComponent::getTextureId()
{
	return this->textureId;
}

} // namespace
