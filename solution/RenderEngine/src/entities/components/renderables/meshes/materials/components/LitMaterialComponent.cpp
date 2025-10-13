#include "LitMaterialComponent.h"
#include "FloatEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(LitMaterialComponent, LIT_MATERIAL)

LitMaterialComponent::LitMaterialComponent(ABaseMaterial* material) : AMaterialComponent(material), shininess(50)
{
	this->addEditorProperty(new FloatEditorProperty{ "Shininess", &this->shininess });
}

void LitMaterialComponent::setShininess(float shininess)
{
	this->shininess = shininess;
}

float LitMaterialComponent::getShininess()
{
	return this->shininess;
}

} // namespace
