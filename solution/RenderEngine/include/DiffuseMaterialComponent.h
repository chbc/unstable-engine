#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class Texture;

class SRE_API DiffuseMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
    class Texture* texture;
	
public:
	DiffuseMaterialComponent(Material *material);

protected:
	virtual ETextureMap::Type getTextureType();
};

} // namespace
