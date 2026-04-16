#define RYML_SINGLE_HDR_DEFINE_NOW
#include "rapidyaml.hpp"

#include "ComponentParser.h"
#include "TransformComponent.h"
#include "EngineValues.h"

namespace sre
{

void ComponentParser::serialize(c4::yml::NodeRef& componentNode, AEntityComponent* component)
{
	componentNode |= ryml::MAP;

	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = componentNode[property->title.c_str()];
		property->serialize(propertyNode);
	}
}

void ComponentParser::deserialize(c4::yml::ConstNodeRef& componentNode, Entity* entity)
{
	if (!componentNode.has_children())
	{
		return;
	}

	c4::yml::ConstNodeRef dataNode = componentNode.first_child();

	std::string type;
	c4::csubstr key = dataNode.key();
	type.assign(key.str, key.len);

	AEntityComponent* component = nullptr;
	if (type == "TransformComponent")
	{
		component = entity->getComponent<TransformComponent>();
	}
	else
	{
		component = entity->addComponent(type.c_str());
	}

	for (const auto& property : component->editorProperties)
	{
		const char* propTitle = property->title.c_str();
		if (dataNode.has_child(c4::to_csubstr(propTitle)))
		{
			c4::yml::ConstNodeRef propertyNode = dataNode[c4::to_csubstr(propTitle)];
			property->deserialize(propertyNode);
		}
	}
}

} // namespace
