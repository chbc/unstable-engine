#pragma once

#include "AMaterialComponent.h"

namespace sre
{

class ABaseMaterial;
class Texture;

class SRE_API PBRMaterialComponent : public AMaterialComponent
{
	DECLARE_MATERIAL_COMPONENT()

protected:
	Texture* albedoTexture{ nullptr };
	Texture* normalTexture{ nullptr };
	Texture* metallicTexture{ nullptr };
	Texture* roughnessTexture{ nullptr };
	Texture* aoTexture{ nullptr };

public:
	PBRMaterialComponent(ABaseMaterial* material);
	~PBRMaterialComponent();

	uint32_t getAlbedoTextureID() const;
	uint32_t getNormalTextureID() const;
	uint32_t getMetallicTextureID() const;
	uint32_t getRoughnessTextureID() const;
	uint32_t getAOTextureID() const;
	float getNormalFlipGreenChannelValue() const;
};

} // namespace
