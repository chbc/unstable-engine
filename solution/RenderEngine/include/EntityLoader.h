#pragma once

#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

class Entity;

class EntityLoader
{
public:
	void save(Entity* entity, const char* fileName);
	Entity* load(const char* fileName, std::string name);
};

} // namespace
