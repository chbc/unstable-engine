#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API DiffuseMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()
	
public:
	DiffuseMaterialComponent(ABaseMaterial *material);
};

} // namespace
