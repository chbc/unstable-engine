#include "EntityParser.h"
#include "AScene.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

#include <sstream>

namespace sre
{
void EntityParser::serialize(c4::yml::NodeRef& entityNode, Entity* entity)
{
	entityNode |= ryml::MAP;

	serializeProperties(entityNode, entity);
	serializeComponents(entityNode, entity);
	serializeChildren(entityNode, entity);
}

void EntityParser::serializeProperties(c4::yml::NodeRef& entityNode, Entity* entity)
{
	for (const SPTR<AEditorProperty>& property : entity->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = entityNode[property->title.c_str()];
		property->serialize(propertyNode);
	}
}

void EntityParser::serializeComponents(c4::yml::NodeRef& entityNode, Entity* entity)
{
	c4::yml::NodeRef ComponentsNode = entityNode["Components"];
	ComponentsNode |= ryml::MAP;
	for (const auto& componentItem : entity->componentsMap)
	{
		AEntityComponent* component = componentItem.second.get();
		c4::yml::NodeRef itemtNode = ComponentsNode[component->getClassName()];
		ComponentParser::serialize(itemtNode, component);
	}
}

void EntityParser::serializeChildren(c4::yml::NodeRef& entityNode, Entity* entity)
{
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

void EntityParser::deserialize(c4::yml::ConstNodeRef& entityNode, Entity* entity)
{
	bool enabled;
	entityNode["Enabled"] >> enabled;
	entity->setEnabled(enabled);

	for (c4::yml::ConstNodeRef propertyNode : entityNode.children())
	{
		if (propertyNode.key() == "Components")
		{
			deserializeComponents(propertyNode, entity);
		}
		else if (propertyNode.key() == "Entities")
		{
			deserializeChildren(propertyNode, entity);
		}
	}

	for (const SPTR<AEditorProperty>& property : entity->editorProperties)
	{
		c4::yml::ConstNodeRef& propertyNode = entityNode[property->title.c_str()];
		property->deserialize(propertyNode);
	}
}

void EntityParser::deserializeComponents(c4::yml::ConstNodeRef& propertyNode, Entity* entity)
{
	for (c4::yml::ConstNodeRef componentNode : propertyNode.children())
	{
		ComponentParser::deserialize(componentNode, entity);
	}
}

void EntityParser::deserializeChildren(c4::yml::ConstNodeRef& propertyNode, Entity* entity)
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	for (c4::yml::ConstNodeRef childEntityNode : propertyNode.children())
	{
		std::ostringstream keyStream;
		keyStream << childEntityNode.key();
		std::string childName = keyStream.str();
		std::string className;

		if (childEntityNode.has_child("Class"))
		{
			childEntityNode["Class"] >> className;
		}

		if (childEntityNode.has_child("FileName"))
		{
			std::string fileName;
			childEntityNode["FileName"] >> fileName;
			Entity* childEntity = assetsManager->loadEntity(fileName.c_str(), childName, className.c_str());
			entity->addChild(childEntity);
		}
		else if (childEntityNode.has_child("Class"))
		{
			Entity* childEntity = entity->createChild(childName, className.c_str());
			deserialize(childEntityNode, childEntity);
		}
		else
		{
			std::ostringstream keyStream;
			keyStream << childEntityNode.key();
			Entity* childEntity = entity->createChild(childName);
			deserialize(childEntityNode, childEntity);
		}
	}
}

} // namespace
