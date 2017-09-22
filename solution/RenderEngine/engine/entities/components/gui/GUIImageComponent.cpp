#include "GUIImageComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/systems/multimedia/textures/Texture.h>
#include <engine/systems/multimedia/textures/AtlasManager.h>
#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/systems/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

GUIImageComponent::GUIImageComponent(Entity *entity) : AEntityComponent(entity) 
{
	this->setUIPosition(glm::vec2(0.0f, 0.0f));
}

void GUIImageComponent::load(const std::string &fileName)
{
	Texture *texture = RenderManager::getInstance()->loadDiffuseTexture(fileName);

	float width = texture->getWidth() / MultimediaManager::getInstance()->getScreenWidth();
	float height = texture->getHeight() / MultimediaManager::getInstance()->getScreenHeight();

	this->meshData = PrimitiveMeshFactory::createPlane2D(width, height);
	this->textureId = texture->getId();
}

void GUIImageComponent::loadFromAtlas(const std::string &fileName, const std::string &imageId)
{
	Atlas *atlas = AtlasManager::getInstance()->getAtlas(fileName);

	const Rect uv = atlas->getItem(imageId);
	this->meshData = PrimitiveMeshFactory::createPlane2D(uv.size.x, uv.size.y, uv);
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
