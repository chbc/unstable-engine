#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class SRE_API NormalMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

public:
	NormalMaterialComponent(ABaseMaterial *material);
};

} // namespace
