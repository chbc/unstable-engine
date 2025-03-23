#pragma once

#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

class Entity;

class EntityLoader
{
public:
	void save(Entity* entity, const char* filePath);
	Entity* load(const char* filePath, std::string name);
};

} // namespace
