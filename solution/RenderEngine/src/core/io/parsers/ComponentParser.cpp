#define RYML_SINGLE_HDR_DEFINE_NOW
#include <rapidyaml/rapidyaml.hpp>

#include "ComponentParser.h"

#include "TransformComponent.h"
#include "PrimitiveMeshFactory.h"
#include "EngineValues.h"

namespace sre
{

void ComponentParser::serialize(c4::yml::NodeRef& componentNode, AEntityComponent* component)
{
	componentNode |= ryml::MAP;

	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = componentNode[property->title.c_str()];
		property->setSaved();
		property->serialize(propertyNode);
	}
}

void ComponentParser::deserialize(c4::yml::ConstNodeRef& componentNode, Entity* entity)
{
	std::ostringstream keyStream;
	keyStream << componentNode.key();
	std::string type = keyStream.str();

	AEntityComponent* component = nullptr;
	if (type == "TransformComponent")
	{
		component = entity->getComponent<TransformComponent>();
	}
	else
	{
		component = entity->addComponent(type.c_str());
	}

	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::ConstNodeRef& propertyNode = componentNode[property->title.c_str()];
		property->deserialize(propertyNode);
	}
}

} // namespace
