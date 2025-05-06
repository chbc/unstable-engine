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
	: AEntityComponent(entity),
        maxItems(0), isDynamic(false)
{
	this->textureEditorProperty = new TextureEditorProperty{ "Texture", &this->texture, ETextureMap::GUI };
	this->addEditorProperty(this->textureEditorProperty);
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

uint32_t GUIImageComponent::getTextureId()
{
    return this->texture->getId();
}

bool GUIImageComponent::isAbleToBeRendered()
{
    return
    (
        (this->meshData != nullptr) &&
        !this->meshData->indices.empty()
    );
}

void GUIImageComponent::onPropertyDeserialized()
{
	AEntityComponent::onPropertyDeserialized();

    AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
    this->meshData = assetsManager->loadMesh2D();
}

void GUIImageComponent::load(const std::string& filePath)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();

    Texture* texture = assetsManager->loadTexture(filePath.c_str(), ETextureMap::GUI);
    glm::vec2 textureSize(texture->getWidth(), texture->getHeight());
    glm::vec2 normalizedSize = singletonsManager->get<MultimediaManager>()->getNormalizedSize(textureSize);

    this->meshData = assetsManager->loadMesh2D();
    this->texture = texture;
	this->textureEditorProperty->setTextureId(reinterpret_cast<void*>(texture->getId()));
	this->getTransform()->setScale(glm::vec3(normalizedSize, 1.0f));
}

void GUIImageComponent::load(const std::string& filePath, const glm::vec2& normalizedSize)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();
    Texture* texture = assetsManager->loadTexture(filePath.c_str(), ETextureMap::GUI);

    this->meshData = assetsManager->loadMesh2D();
    this->texture = texture;
    this->textureEditorProperty->setTextureId(reinterpret_cast<void*>(texture->getId()));
    this->getTransform()->setScale(glm::vec3(normalizedSize, 1.0f));
}

void GUIImageComponent::loadFromAtlas(const std::string& filePath, const std::string& imageId)
{
    /*
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();

    Atlas* atlas = SingletonsManager::getInstance()->get<AtlasManager>()->getAtlas(filePath);
    this->texture = atlas->getTexture();
    const AtlasItem* atlasItem = atlas->getItem(imageId);
    this->meshData = PrimitiveMeshFactory().createPlaneTopDown(atlasItem->normalizedSize, atlasItem->uv);
    this->extent = atlasItem->normalizedSize;
    */
}

} // namespace
