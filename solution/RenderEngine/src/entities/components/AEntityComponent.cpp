#include "AEntityComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "BoolEditorProperty.h"

namespace sre
{

uint16_t AEntityComponent::Index = 0;

AEntityComponent::AEntityComponent(Entity* arg_entity) : entity(arg_entity), enabled(true)
{
	this->addEditorProperty(new BoolEditorProperty{ "Enabled", &this->enabled });
}

AEntityComponent::~AEntityComponent()
{
	this->editorProperties.clear();
}

AEntityComponent* AEntityComponent::Create(const char* className, Entity* entity)
{
	EntityComponentTypes* types = EntityComponentTypes::getInstance();
	size_t key = std::hash<std::string>{}(className);

	assert(types->typesMap.count(key) > 0);

	AEntityComponent* result = types->typesMap[key](entity);
	result->checkAndRefreshId();
	return result;
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
	editorProperty->onValueChanged = std::bind(&AEntityComponent::onValueChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

} // namespace
