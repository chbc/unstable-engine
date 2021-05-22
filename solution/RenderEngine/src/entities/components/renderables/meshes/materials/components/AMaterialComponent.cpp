#include "AMaterialComponent.h"

namespace sre
{

AMaterialComponent::AMaterialComponent(Material* arg_material) : material(arg_material)
{ }

void AMaterialComponent::addEditorProperty(AEditorProperty* editorProperty)
{
	this->editorProperties.push_back(SPTR<AEditorProperty>(editorProperty));
}

} //
