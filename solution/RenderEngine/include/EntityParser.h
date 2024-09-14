#pragma once

#include "ComponentParser.h"

namespace sre
{

class Entity;

class EntityParser
{
private:
	static void serialize(c4::yml::NodeRef& entityNode, Entity* entity);
	static void deserialize(c4::yml::ConstNodeRef& entityNode, Entity* entity);

friend class SceneLoader;
};

} // namespace
