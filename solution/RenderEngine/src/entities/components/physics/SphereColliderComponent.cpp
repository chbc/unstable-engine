#include "SphereColliderComponent.h"
#include "FloatEditorProperty.h"

namespace sre
{

IMPLEMENT_CHILD_COMPONENT(SphereColliderComponent, AColliderComponent)

SphereColliderComponent::SphereColliderComponent(Entity* entity)
	: AColliderComponent(entity, ECollisionType::SPHERE)
{
	this->addEditorProperty(new FloatEditorProperty("Radius", &this->radius));
}

} // namespace
