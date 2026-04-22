#include "SphereColliderComponent.h"
#include "FloatEditorProperty.h"
#include "Entity.h"

namespace sre
{

IMPLEMENT_CHILD_COMPONENT(SphereColliderComponent, AColliderComponent)

SphereColliderComponent::SphereColliderComponent(Entity* entity)
	: AColliderComponent(entity, ECollisionType::SPHERE)
{
	entity->getBounds(this->bounds);
	this->addEditorProperty(new FloatEditorProperty("Radius", &this->bounds.halfExtents.x));
}

float SphereColliderComponent::getRadius() const
{
	return this->bounds.getRadius();
}

} // namespace
