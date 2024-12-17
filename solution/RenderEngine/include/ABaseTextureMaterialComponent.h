#pragma once

#include "AMaterialComponent.h"
#include "EMaterialMap.h"

namespace sre
{

class Texture;

class SRE_API ABaseTextureMaterialComponent : public AMaterialComponent
{
protected:
	class Texture* texture;

public:
	ABaseTextureMaterialComponent(Material* material);
	void load(const char* fileName);
	uint32_t getTextureID() const;

protected:
	virtual ETextureMap::Type getTextureType() = 0;
};

} // namespace
