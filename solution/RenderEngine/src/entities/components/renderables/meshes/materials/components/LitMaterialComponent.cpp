#include "LitMaterialComponent.h"
#include "FloatEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(LitMaterialComponent, LIT_MATERIAL)

LitMaterialComponent::LitMaterialComponent(ABaseMaterial* material) : AMaterialComponent(material)
{ }

} // namespace
