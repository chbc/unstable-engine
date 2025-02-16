#include "EntityParser.h"
#include "AScene.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

#include <sstream>

namespace sre
{
void EntityParser::serialize(c4::yml::NodeRef& entityNode, Entity* entity)
{
	serializeProperties(entityNode, entity);
	serializeComponents(entityNode, entity);
	serializeChildren(entityNode, entity);
}

void EntityParser::serializeProperties(c4::yml::NodeRef& entityNode, Entity* entity)
{
	entityNode |= ryml::MAP;
	for (const SPTR<AEditorProperty>& property : entity->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = entityNode[property->title.c_str()];
		property->setSaved();
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

	for (c4::yml::ConstNodeRef propertyNode : entityNode.children())
	{
		std::ostringstream keyStream;
		keyStream << propertyNode.key();
		std::string key = keyStream.str();
		if (key == "Components")
		{
			deserializeComponents(propertyNode, entity);
		}
		else if (key == "Entities")
		{
			deserializeChildren(propertyNode, entity);
		}

		AEditorProperty* editorProperty = entity->findProperty(key);
		if (editorProperty != nullptr)
		{
			editorProperty->deserialize(propertyNode);
		}
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
	for (c4::yml::ConstNodeRef entityNode : propertyNode.children())
	{
		std::ostringstream nameStream;
		nameStream << entityNode.key();
		std::string name = nameStream.str();
		std::string fileName;
		std::string className{ "Entity" };

		if (entityNode.has_child("Class"))
		{
			entityNode["Class"] >> className;
		}
		if (entityNode.has_child("FileName"))
		{
			entityNode["FileName"] >> fileName;
		}

		Entity* childEntity = nullptr;
		if (!fileName.empty())
		{
			childEntity = assetsManager->loadEntity(fileName.c_str(), name);
		}
		else
		{
			childEntity = Entity::Create(name, className.c_str());
		}

		entity->addChild(childEntity);

		deserialize(entityNode, childEntity);
	}
}

} // namespace
