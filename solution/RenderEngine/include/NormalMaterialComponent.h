#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API NormalMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
public:
	NormalMaterialComponent(Material *material);

protected:
	virtual ETextureMap::Type getTextureType();
};

} // namespace
