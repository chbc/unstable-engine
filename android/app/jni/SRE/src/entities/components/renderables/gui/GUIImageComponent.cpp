#include "GUIImageComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "AtlasManager.h"
#include "TransformComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

IMPLEMENT_COMPONENT(GUIImageComponent)

GUIImageComponent::GUIImageComponent(Entity *entity, uint32_t arg_maxItems)
    :   ARenderableComponent(entity),
        extent(glm::vec2(0.0f, 0.0f)), pivot(glm::vec2(0.0f, 0.0f)),
        maxItems(arg_maxItems), isDynamic(arg_maxItems > 0)
{
    this->setUIPosition(glm::vec2(0.0f, 0.0f));
}

void GUIImageComponent::setUIPosition(const glm::vec2 &position)
{
    glm::vec3 realPosition = glm::vec3
    (
        ((position.x * 2) - 1), 
        -(position.y * 2) + 1, 
        0.0f
    );

    realPosition.x -= this->pivot.x;
    realPosition.y += this->pivot.y;

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

glm::vec2 GUIImageComponent::getExtent()
{
    glm::vec3 scale = this->getTransform()->getScale();
    return glm::vec2(this->extent.x * scale.x, this->extent.y * scale.y);
}

void GUIImageComponent::setPivot(const glm::vec2& pivot)
{
    this->pivot = pivot;
}

void GUIImageComponent::load(const std::string& fileName)
{
    Texture* texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::GUI);
    glm::vec2 textureSize(texture->getWidth(), texture->getHeight());
    glm::vec2 normalizedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(textureSize);

    GUIMeshData* plane = PrimitiveMeshFactory().createPlaneTopDown(normalizedSize);
    this->meshData = UPTR<GUIMeshData>{ plane };
    this->textureId = texture->getId();
    this->extent = normalizedSize;
}

void GUIImageComponent::load(const std::string& fileName, const glm::vec2& normalizedSize)
{
    Texture* texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::GUI);
    glm::vec2 textureSize(texture->getWidth(), texture->getHeight());

    GUIMeshData* plane = PrimitiveMeshFactory().createPlaneTopDown(normalizedSize);
    this->meshData = UPTR<GUIMeshData>{ plane };
    this->textureId = texture->getId();
    this->extent = normalizedSize;
}

void GUIImageComponent::loadFromAtlas(const std::string& fileName, const std::string& imageId)
{
    Atlas* atlas = SingletonsManager::getInstance()->resolve<AtlasManager>()->getAtlas(fileName);

    const AtlasItem* atlasItem = atlas->getItem(imageId);

    GUIMeshData* plane = PrimitiveMeshFactory().createPlaneTopDown(atlasItem->normalizedSize, atlasItem->uv);
    this->meshData = UPTR<GUIMeshData>{ plane };
    this->textureId = atlas->getTextureId();
    this->extent = atlasItem->normalizedSize;
}

} // namespace
