#include "PBRMaterialComponent.h"
#include "Texture.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "NormalTextureEditorProperty.h"
#include "Material.h"
#include "ColorMaterialComponent.h"

namespace sre
{

IMPLEMENT_MATERIAL_COMPONENT(PBRMaterialComponent, PBR_MATERIAL)

PBRMaterialComponent::PBRMaterialComponent(Material* material)
	: AMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Albedo", &this->albedoTexture, ETextureMap::DIFFUSE });
	this->addEditorProperty(new NormalTextureEditorProperty{ "Normal", &this->normalTexture });
	this->addEditorProperty(new TextureEditorProperty{ "Metallic", &this->metallicTexture, ETextureMap::METALLIC });
	this->addEditorProperty(new TextureEditorProperty{ "Roughness", &this->roughnessTexture, ETextureMap::ROUGHNESS });
	this->addEditorProperty(new TextureEditorProperty{ "Ambient Occlusion", &this->aoTexture, ETextureMap::AMBIENT_OCCLUSION });

	material->removeComponent<ColorMaterialComponent>();
}

PBRMaterialComponent::~PBRMaterialComponent()
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	assetsManager->releaseTexture(this->albedoTexture);
	assetsManager->releaseTexture(this->normalTexture);
	assetsManager->releaseTexture(this->metallicTexture);
	assetsManager->releaseTexture(this->roughnessTexture);
	assetsManager->releaseTexture(this->aoTexture);
}

uint32_t PBRMaterialComponent::getAlbedoTextureID() const
{
	return this->albedoTexture->getId();
}

uint32_t PBRMaterialComponent::getNormalTextureID() const
{
	return this->normalTexture->getId();
}

uint32_t PBRMaterialComponent::getMetallicTextureID() const
{
	return this->metallicTexture->getId();
}

uint32_t PBRMaterialComponent::getRoughnessTextureID() const
{
	return this->roughnessTexture->getId();
}

uint32_t PBRMaterialComponent::getAOTextureID() const
{
	return aoTexture->getId();
}

float PBRMaterialComponent::getNormalFlipGreenChannelValue() const
{
	float result = this->normalTexture->getFlipGreenChannel() ? 1.0f : 0.0f;
	return result;
}

} // namespace
