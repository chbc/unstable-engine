#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

class Texture;

class SRE_API DiffuseMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()
	
public:
	DiffuseMaterialComponent(Material *material);
};

} // namespace
