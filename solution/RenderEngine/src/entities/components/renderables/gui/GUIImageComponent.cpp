#include "GUIImageComponent.h"
#include "RenderManager.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "AtlasManager.h"
#include "TransformComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

GUIImageComponent::GUIImageComponent(Entity *entity, uint32_t arg_maxItems)
    :   ARenderableComponent(entity), 
        maxItems(arg_maxItems), isDynamic(arg_maxItems > 0)
{
    this->setUIPosition(glm::vec2(0.0f, 0.0f));
}

void GUIImageComponent::load(const std::string &fileName)
{
    Texture *texture = SingletonsManager::getInstance()->resolve<RenderManager>()->loadGUITexture(fileName);
    glm::vec2 pixelSize(texture->getWidth(), texture->getHeight());
    glm::vec2 screenBasedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(pixelSize);

	GUIMeshData* plane = PrimitiveMeshFactory().createPlaneTopDown(screenBasedSize);
	this->meshData = UPTR<GUIMeshData>{ plane };
    this->textureId = texture->getId();
}

void GUIImageComponent::loadFromAtlas(const std::string &fileName, const std::string &imageId)
{
    Atlas *atlas = SingletonsManager::getInstance()->resolve<AtlasManager>()->getAtlas(fileName);

    const AtlasItem *atlasItem = atlas->getItem(imageId);

	GUIMeshData *plane = PrimitiveMeshFactory().createPlaneTopDown(atlasItem->normalizedSize, atlasItem->uv);
	this->meshData = UPTR<GUIMeshData>{ plane };
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
