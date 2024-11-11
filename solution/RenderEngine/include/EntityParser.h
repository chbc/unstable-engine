#pragma once

#include "ComponentParser.h"

namespace sre
{

class Entity;
class AScene;

class EntityParser
{
private:
	static void serialize(c4::yml::NodeRef& entityNode, Entity* entity);
	static void deserialize(AScene* scene, c4::yml::ConstNodeRef& entityNode, Entity* entity);

friend class SceneLoader;
};

} // namespace
