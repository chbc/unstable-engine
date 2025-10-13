#pragma once

#include "ABaseTextureMaterialComponent.h"

namespace sre
{

using TexturesMap = std::unordered_map<std::string, Texture*>;

class SRE_API CustomMaterialComponent : public ABaseTextureMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()
	
private:
	TexturesMap texturesMap;

public:
	CustomMaterialComponent(ABaseMaterial *material);
	AEditorProperty* addTextureProperty(const std::string& uniformVariable);
	TexturesMap& getTexturesMap();
};

} // namespace
