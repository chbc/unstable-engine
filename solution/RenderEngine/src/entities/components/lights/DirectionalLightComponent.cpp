#include "DirectionalLightComponent.h"
#include "XYZEditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(DirectionalLightComponent)

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
	this->addEditorProperty(new XYZEditorProperty{ "Direction", this->direction });
}

void DirectionalLightComponent::setDirection(const glm::vec3 &direction)
{
	this->direction = direction;
}

glm::vec3 DirectionalLightComponent::getDirection()
{
    return this->direction;
}

} // namespace
