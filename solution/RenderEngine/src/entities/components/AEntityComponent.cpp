#include "AEntityComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

namespace sre
{

uint16_t AEntityComponent::Index = 0;

AEntityComponent::~AEntityComponent()
{
	this->editorProperties.clear();
}

uint16_t AEntityComponent::generateId()
{
	return Index++;
}

TransformComponent *AEntityComponent::getTransform()
{
	return this->entity->getTransform();
}

void AEntityComponent::setEnabled(bool value)
{
	this->enabled = value;
}

bool AEntityComponent::isEnabled() const
{
	return this->enabled;
}

void AEntityComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	this->editorProperties.emplace_back(editorProperty);
}

} // namespace
