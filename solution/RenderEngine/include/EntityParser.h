#pragma once

#include "ComponentParser.h"

namespace sre
{

class Entity;
class Scene;

class EntityParser
{
private:
	static void serialize(c4::yml::NodeRef& entityNode, Entity* entity);
	static void deserialize(Scene* scene, c4::yml::ConstNodeRef& entityNode, Entity* entity);

friend class SceneLoader;
};

} // namespace
