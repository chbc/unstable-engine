#include "ColorMaterialComponent.h"
#include "../Material.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

ColorMaterialComponent::ColorMaterialComponent(Material *material) : AMaterialComponent(material)
{
	this->color = glm::vec4{ 1.0f };
}

void ColorMaterialComponent::setColor(const glm::vec4 &color)
{
	this->color = color;
}

glm::vec4 ColorMaterialComponent::getColor()
{
	return this->color;
}

} // namespace
