#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API SpriteMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

public:
	SpriteMaterialComponent(Material* material);
};
	
} // namespace
