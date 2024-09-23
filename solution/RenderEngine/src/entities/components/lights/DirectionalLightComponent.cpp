#include "DirectionalLightComponent.h"
#include "Vec3EditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(DirectionalLightComponent)

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
	this->addEditorProperty(new Vec3EditorProperty{ "Direction", &this->direction });
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
