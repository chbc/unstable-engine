#include "AEntityComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

namespace sre
{

uint16_t AEntityComponent::Index = 0;

TransformComponent *AEntityComponent::getTransform()
{
	return this->entity->getTransform();
}

uint16_t AEntityComponent::generateId()
{
	return Index++;
}

} // namespace
