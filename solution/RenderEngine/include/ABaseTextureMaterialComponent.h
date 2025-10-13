#pragma once

#include "AMaterialComponent.h"
#include "ETextureMap.h"

namespace sre
{

class Texture;
class ABaseMaterial;

class SRE_API ABaseTextureMaterialComponent : public AMaterialComponent
{
protected:
	Texture* texture;

public:
	ABaseTextureMaterialComponent(ABaseMaterial* material);
	virtual ~ABaseTextureMaterialComponent();
	uint32_t getTextureID() const;
};

} // namespace
