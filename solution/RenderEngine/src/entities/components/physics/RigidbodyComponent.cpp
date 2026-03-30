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

} // namespace
