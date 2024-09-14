#include "EntityParser.h"

namespace sre
{
void EntityParser::serialize(c4::yml::NodeRef& entityNode, Entity* entity)
{
	entityNode |= ryml::MAP;

	entityNode["enabled"] << entity->isEnabled();

	for (const auto& componentItem : entity->componentsMap)
	{
		AEntityComponent* component = componentItem.second.get();
		c4::yml::NodeRef componentNode = entityNode[component->getClassName()];
		ComponentParser::serialize(componentNode, component);
	}
}

void EntityParser::deserialize(c4::yml::ConstNodeRef& entityNode, Entity* entity)
{
	bool enabled;
	entityNode["enabled"] >> enabled;
	entity->setEnabled(enabled);

	for (c4::yml::ConstNodeRef componentNode : entityNode.children())
	{
		if (componentNode.is_map())
		{
			ComponentParser::deserialize(componentNode, entity);
		}
	}
}

} // namespace
