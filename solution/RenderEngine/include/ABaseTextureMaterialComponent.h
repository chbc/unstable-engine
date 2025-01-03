#pragma once

#include "AMaterialComponent.h"
#include "ETextureMap.h"

namespace sre
{

class Texture;

class SRE_API ABaseTextureMaterialComponent : public AMaterialComponent
{
protected:
	class Texture* texture;

public:
	ABaseTextureMaterialComponent(Material* material);
	virtual ~ABaseTextureMaterialComponent();
	uint32_t getTextureID() const;
};

} // namespace
