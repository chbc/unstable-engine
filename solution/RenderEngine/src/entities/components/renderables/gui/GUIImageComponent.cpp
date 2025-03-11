#include "GUIImageComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "AtlasManager.h"
#include "TransformComponent.h"
#include "PrimitiveMeshFactory.h"
#include "Vec2EditorProperty.h"
#include "TextureEditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(GUIImageComponent)

GUIImageComponent::GUIImageComponent(Entity *entity)
	: AEntityComponent(entity), uiPosition(glm::vec2(0.0f, 0.0f)), extent(glm::vec2(0.0f, 0.0f)), pivot(glm::vec2(0.0f, 0.0f)),
        maxItems(0), isDynamic(false)
{
	this->addEditorProperty(new TextureEditorProperty{ "Texture", &this->texture, ETextureMap::GUI });
	this->addEditorProperty(new Vec2EditorProperty{ "UI Position", &this->uiPosition });
	this->addEditorProperty(new Vec2EditorProperty{ "Extent", &this->extent });
	this->addEditorProperty(new Vec2EditorProperty{ "Pivot", &this->pivot });

    this->setUIPosition(glm::vec2(0.0f, 0.0f));
}

GUIImageComponent::~GUIImageComponent()
{
    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    assetsManager->releaseTexture(this->texture);
}

void GUIImageComponent::setMaxItems(uint32_t arg_maxItems)
{
    maxItems = arg_maxItems;
}

void GUIImageComponent::setUIPosition(const glm::vec2 &position)
{
    this->uiPosition = position;
    this->updateTransform();
}

glm::vec2 GUIImageComponent::getUIPosition()
{
    return this->uiPosition;
}

uint32_t GUIImageComponent::getTextureId()
{
    return this->texture->getId();
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

bool GUIImageComponent::isAbleToBeRendered()
{
    return
    (
        (this->meshData != nullptr) &&
        !this->meshData->indices.empty()
    );
}

void GUIImageComponent::onPropertyChanged()
{
	this->updateTransform();
}

void GUIImageComponent::load(const std::string& fileName)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();

    Texture* texture = assetsManager->loadTexture(fileName.c_str(), ETextureMap::GUI);
    glm::vec2 textureSize(texture->getWidth(), texture->getHeight());
    glm::vec2 normalizedSize = singletonsManager->get<MultimediaManager>()->getNormalizedSize(textureSize);

    this->meshData = assetsManager->loadGUIMeshData();
    this->texture = texture;
    this->extent = normalizedSize;
}

void GUIImageComponent::load(const std::string& fileName, const glm::vec2& normalizedSize)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();

    Texture* texture = assetsManager->loadTexture(fileName.c_str(), ETextureMap::GUI);
    glm::vec2 textureSize(texture->getWidth(), texture->getHeight());

    this->meshData = assetsManager->loadGUIMeshData();
    this->texture = texture;
    this->extent = normalizedSize;
}

void GUIImageComponent::loadFromAtlas(const std::string& fileName, const std::string& imageId)
{
    /*
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();

    Atlas* atlas = SingletonsManager::getInstance()->get<AtlasManager>()->getAtlas(fileName);
    this->texture = atlas->getTexture();
    const AtlasItem* atlasItem = atlas->getItem(imageId);
    this->meshData = PrimitiveMeshFactory().createPlaneTopDown(atlasItem->normalizedSize, atlasItem->uv);
    this->extent = atlasItem->normalizedSize;
    */
}

// XXX PAREI AQUI
void GUIImageComponent::updateTransform()
{
    glm::vec3 realPosition = glm::vec3
    (
        ((this->uiPosition.x * 2) - (1 + (this->extent.x * this->pivot.x))),
        -(this->uiPosition.y * 2) + 1,
        0.0f
    );

	TransformComponent* transform = this->getTransform();
    transform->setPosition(realPosition);
	transform->setScale(glm::vec3(this->extent, 1.0f));
}

} // namespace
