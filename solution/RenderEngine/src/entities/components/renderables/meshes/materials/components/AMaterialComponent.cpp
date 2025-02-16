#include "AMaterialComponent.h"
#include "assert.h"

namespace sre
{

AMaterialComponent::AMaterialComponent(Material* arg_material) : material(arg_material)
{ }

void AMaterialComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	editorProperty->onValueDeserializedCallback = std::bind(&AMaterialComponent::onValueDeserialized, this);
	editorProperty->onValueChangedCallback = std::bind(&AMaterialComponent::onValueChanged, this);
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
