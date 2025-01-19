#pragma once

#include "ComponentParser.h"

namespace sre
{

class Entity;

class EntityParser
{
private:
	static void serialize(c4::yml::NodeRef& entityNode, Entity* entity);
	static void serializeProperties(c4::yml::NodeRef& entityNode, Entity* entity);
	static void serializeComponents(c4::yml::NodeRef& entityNode, Entity* entity);
	static void serializeChildren(c4::yml::NodeRef& entityNode, Entity* entity);

	static void deserialize(c4::yml::ConstNodeRef& entityNode, Entity* entity);

	static void deserializeComponents(c4::yml::ConstNodeRef& propertyNode, Entity* entity);
	static void deserializeChildren(c4::yml::ConstNodeRef& propertyNode, Entity* entity);

friend class SceneLoader;
friend class EntityLoader;
};

} // namespace
