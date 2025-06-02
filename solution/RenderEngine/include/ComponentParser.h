#pragma once

#include "rapidyaml.hpp"
#include "Entity.h"

namespace sre
{

class AEntityComponent;

class ComponentParser
{
private:
	static void serialize(c4::yml::NodeRef& componentNode, AEntityComponent* component);
	static void deserialize(c4::yml::ConstNodeRef& componentNode, Entity* entity);

friend class EntityParser;
};

} // namespace
