#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Vec3EditorProperty.h"

namespace sre
{

IMPLEMENT_CHILD_COMPONENT(BoxColliderComponent, AColliderComponent)

BoxColliderComponent::BoxColliderComponent(Entity* entity) 
	: AColliderComponent(entity, ECollisionType::BOX)
{
	entity->getBounds(this->bounds);
	this->addEditorProperty(new Vec3EditorProperty("Half Extents", &this->bounds.halfExtents, 0.5f));
}

bool BoxColliderComponent::intersects(BoxColliderComponent* other)
{
	const glm::vec3& position = this->getTransform()->getPosition();
	const glm::vec3& otherPosition = other->getTransform()->getPosition();

	return this->bounds.intersects(position, otherPosition, other->bounds);
}

} // namespace
