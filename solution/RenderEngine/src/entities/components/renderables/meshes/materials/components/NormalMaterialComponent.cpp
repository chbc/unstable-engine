#include "NormalMaterialComponent.h"
#include "Texture.h"
#include "NormalTextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(NormalMaterialComponent, NORMAL_MATERIAL)

NormalMaterialComponent::NormalMaterialComponent(ABaseMaterial *material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new NormalTextureEditorProperty{ "Normal", &this->texture });
}

} // namespace
