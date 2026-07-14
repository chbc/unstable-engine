#pragma once

#include <string>

namespace sre
{
class Entity;
class AScene;

class EntityLoader
{
public:
	void save(Entity* entity, const char* filePath);
	Entity* load(const char* filePath, std::string name, AScene* scene);
};

} // namespace
