#include "ColorMaterialComponent.h"
#include "Material.h"
#include "ColorEditorProperty.h"

#include <glm/gtc/type_ptr.hpp>

namespace sre
{

IMPLEMENT_MATERIAL_COMPONENT(ColorMaterialComponent, COLOR_MATERIAL)

ColorMaterialComponent::ColorMaterialComponent(Material *material) : AMaterialComponent(material)
{
	this->color = glm::vec4{ 1.0f };

	this->addEditorProperty(new ColorEditorProperty{"Color", this->color });
}

void ColorMaterialComponent::setColor(const glm::vec4 &color)
{
	this->color = color;
}

glm::vec4 ColorMaterialComponent::getColor()
{
	return this->color;
}

void ColorMaterialComponent::getColor(float* result)
{
	result = glm::value_ptr(this->color);
}

} // namespace
