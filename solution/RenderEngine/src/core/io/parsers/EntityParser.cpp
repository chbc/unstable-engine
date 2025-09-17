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
	if (entity->isAsset() && entity->isPropertiesStored())
	{
		return;
	}

	entityNode |= ryml::MAP;
	for (const SPTR<AEditorProperty>& property : entity->editorProperties)
	{
		if (!entity->isAsset() || !property->isStored())
		{
			c4::yml::NodeRef& propertyNode = entityNode[property->title.c_str()];
			property->serialize(propertyNode);
		}
	}

	entity->setPropertiesSaved();
}

void EntityParser::serializeComponents(c4::yml::NodeRef& entityNode, Entity* entity)
{
	if (entity->isAsset() && entity->isComponentsStored())
	{
		return;
	}

	c4::yml::NodeRef ComponentsNode = entityNode["Components"];
	ComponentsNode |= ryml::MAP;
	for (const auto& componentItem : entity->componentsMap)
	{
		AEntityComponent* component = componentItem.second.get();
		if (!entity->isAsset() || !component->isStored())
		{
			c4::yml::NodeRef itemtNode = ComponentsNode[component->getClassName()];
			ComponentParser::serialize(itemtNode, component);
		}
	}

	entity->setComponentsSaved();
}

void EntityParser::serializeChildren(c4::yml::NodeRef& entityNode, Entity* entity)
{
	if (entity->isAsset() && entity->isChildrenStored())
	{
		return;
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

	entity->setChildrenSaved();
}

void EntityParser::deserialize(c4::yml::ConstNodeRef& entityNode, AScene* scene, Entity* entity)
{
	for (c4::yml::ConstNodeRef propertyNode : entityNode.children())
	{
		std::ostringstream keyStream;
		keyStream << propertyNode.key();
		std::string key = keyStream.str();
		AEditorProperty* editorProperty = entity->findProperty(key);
		if (editorProperty != nullptr)
		{
			editorProperty->deserialize(propertyNode);
		}
		else
		{
			if (key == "Components")
			{
				deserializeComponents(propertyNode, entity);
			}
			else if (key == "Entities")
			{
				deserializeChildren(propertyNode, scene, entity);
			}
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

void EntityParser::deserializeChildren(c4::yml::ConstNodeRef& propertyNode, AScene* scene, Entity* entity)
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	for (c4::yml::ConstNodeRef entityNode : propertyNode.children())
	{
		std::ostringstream nameStream;
		nameStream << entityNode.key();
		std::string name = nameStream.str();
		std::string filePath;
		std::string className{ "Entity" };

		Entity* childEntity = nullptr;
		if (entityNode.has_child("FilePath"))
		{
			entityNode["FilePath"] >> filePath;
			childEntity = scene->createEntityFromFile(filePath, entity);
		}
		else
		{
			if (entityNode.has_child("Class"))
			{
				entityNode["Class"] >> className;
			}
			childEntity = scene->createEntity(name, entity, className);
		}

		deserialize(entityNode, scene, childEntity);
	}
}

} // namespace
