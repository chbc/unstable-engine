#include "RigidbodyComponent.h"
#include "FloatEditorProperty.h"
#include "BoolEditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(RigidbodyComponent)

RigidbodyComponent::RigidbodyComponent(Entity* entity) : AEntityComponent(entity)
{
	this->addEditorProperty(new FloatEditorProperty{ "Mass", &this->mass });
	this->addEditorProperty(new FloatEditorProperty{ "Restitution", &this->restitution });
	this->addEditorProperty(new BoolEditorProperty{ "Use Gravity", &this->useGravity });
}

void RigidbodyComponent::setVelocity(const glm::vec3& newVelocity)
{
	this->velocity = newVelocity;
}

void RigidbodyComponent::applyForce(const glm::vec3& force)
{
	this->mass = (this->mass > 0.0f) ? this->mass : 1.0f;
	this->acceleration += force / this->mass;
}

const glm::vec3& RigidbodyComponent::getVelocity() const
{
	return this->velocity;
}

} // namespace
