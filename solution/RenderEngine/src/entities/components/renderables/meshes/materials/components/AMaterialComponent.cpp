#include "AMaterialComponent.h"
#include "assert.h"

namespace sre
{

AMaterialComponent::AMaterialComponent(Material* arg_material) : material(arg_material)
{ }

void AMaterialComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	editorProperty->onValueSerializedCallback = std::bind(&AMaterialComponent::onPropertySerialized, this);
	editorProperty->onValueDeserializedCallback = std::bind(&AMaterialComponent::onPropertyDeserialized, this);
	editorProperty->onValueChangedCallback = std::bind(&AMaterialComponent::onPropertyChanged, this);
	this->editorProperties.emplace_back(editorProperty);
}

AMaterialComponent* AMaterialComponent::Create(const char* className, Material* material)
{
	MaterialComponentTypes* types = MaterialComponentTypes::getInstance();
	size_t key = std::hash<std::string>{}(className);

	assert(types->typesMap.count(key) > 0);

	AMaterialComponent* result = types->typesMap[key](material);
	return result;
}

} //
