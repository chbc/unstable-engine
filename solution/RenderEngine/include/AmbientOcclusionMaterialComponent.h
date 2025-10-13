#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API AmbientOcclusionMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()
	
public:
	AmbientOcclusionMaterialComponent(ABaseMaterial *material);
};

} // namespace
