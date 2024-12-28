#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API SpecularMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()
	
public:
	SpecularMaterialComponent(Material *material);
};

} // namespace
