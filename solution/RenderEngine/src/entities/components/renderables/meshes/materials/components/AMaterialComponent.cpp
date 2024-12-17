#include "AMaterialComponent.h"
#include "assert.h"

namespace sre
{

AMaterialComponent::AMaterialComponent(Material* arg_material) : material(arg_material)
{ }

void AMaterialComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	this->editorProperties.push_back(SPTR<AEditorProperty>(editorProperty));
}

AMaterialComponent* AMaterialComponent::Create(const char* className, Material* material)
{
	MaterialComponentTypes* types = MaterialComponentTypes::getInstance();
	int key = std::hash<std::string>{}(className);

	assert(types->typesMap.count(key) > 0);

	AMaterialComponent* result = types->typesMap[key](material);
	return result;
}

} //
