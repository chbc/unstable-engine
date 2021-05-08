#include "AEntityComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

namespace sre
{

uint16_t AEntityComponent::Index = 0;

AEntityComponent::~AEntityComponent()
{
	this->editorVariables.clear();
}

uint16_t AEntityComponent::generateId()
{
	return Index++;
}

TransformComponent *AEntityComponent::getTransform()
{
	return this->entity->getTransform();
}

} // namespace
