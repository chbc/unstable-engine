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

bool AEntityComponent::isEnabled() const
{
	return this->enabled;
}

void AEntityComponent::setEnabled(bool value)
{
	this->enabled = value;
}

bool AEntityComponent::isSaved() const
{
	return saved;
}

bool AEntityComponent::isStored() const
{
	return this->stored;
}

void AEntityComponent::onPropertySerialized()
{
	if (!this->saved)
	{
		this->saved = true;
	}
}

void AEntityComponent::onPropertyDeserialized()
{
	this->stored = false;
	this->entity->onComponentDeserialized();
}

void AEntityComponent::onPropertyChanged()
{
	this->saved = false;
	this->stored = false;
	this->entity->onComponentChanged();
}

void AEntityComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	editorProperty->onValueSerializedCallback = std::bind(&AEntityComponent::onPropertySerialized, this);
	editorProperty->onValueDeserializedCallback = std::bind(&AEntityComponent::onPropertyDeserialized, this);
	editorProperty->onValueChangedCallback = std::bind(&AEntityComponent::onPropertyChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

void AEntityComponent::clone(AEntityComponent* result)
{
	for (int i = 0; i < this->editorProperties.size(); ++i)
	{
		SPTR<AEditorProperty> destination = result->editorProperties[i];
		this->editorProperties[i]->copy(destination.get());
	}
}

void AEntityComponent::setStored(bool value)
{
	this->stored = value;

	for (auto& item : this->editorProperties)
	{
		item->setStored(value);
	}
}

} // namespace
