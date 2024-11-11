#include "EntityParser.h"
#include "AScene.h"
#include <sstream>

namespace sre
{
void EntityParser::serialize(c4::yml::NodeRef& entityNode, Entity* entity)
{
	entityNode |= ryml::MAP;

	entityNode["Enabled"] << entity->isEnabled(); // XXX
	
	c4::yml::NodeRef ComponentsNode = entityNode["Components"];
	ComponentsNode |= ryml::MAP;
	for (const auto& componentItem : entity->componentsMap)
	{
		AEntityComponent* component = componentItem.second.get();
		c4::yml::NodeRef itemtNode = ComponentsNode[component->getClassName()];
		ComponentParser::serialize(itemtNode, component);
	}

	if (entity->getChildrenCount() > 0)
	{
		c4::yml::NodeRef childNode = entityNode["Entities"];
		childNode |= ryml::MAP;
		for (Entity* item : entity->childrenList)
		{
			c4::yml::NodeRef itemNode = childNode[item->getName()];
			serialize(itemNode, item);
		}
	}
}

void EntityParser::deserialize(AScene* scene, c4::yml::ConstNodeRef& entityNode, Entity* entity)
{
	bool enabled;
	entityNode["Enabled"] >> enabled;
	entity->setEnabled(enabled);

	for (c4::yml::ConstNodeRef propertyNode : entityNode.children())
	{
		if (propertyNode.key() == "Components")
		{
			for (c4::yml::ConstNodeRef componentNode : propertyNode.children())
			{
				ComponentParser::deserialize(componentNode, entity);
			}
		}
		else if (propertyNode.key() == "Entities")
		{
			for (c4::yml::ConstNodeRef childEntityNode : propertyNode.children())
			{
				std::ostringstream keyStream;
				keyStream << childEntityNode.key();
				Entity* childEntity = scene->createEntity(keyStream.str(), entity);
				deserialize(scene, childEntityNode, childEntity);
			}
		}
	}
}

} // namespace
