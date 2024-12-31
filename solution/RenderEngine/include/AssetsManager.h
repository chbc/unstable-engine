#pragma once

#include "Entity.h"
#include "ASingleton.h"
#include "memory_aliases.h"

#include <unordered_map>
#include <string>

namespace sre
{

struct Mesh;
class Material;

using MeshPairType = std::pair<size_t, SPTR<Mesh>>;
using MaterialPairType = std::pair<size_t, SPTR<Material>>;
using EntityPairType = std::pair<size_t, SPTR<Entity>>;

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	// <key, <ref count, asset>
	std::unordered_map<size_t, MeshPairType> meshesMap;
	std::unordered_map<size_t, MaterialPairType> materialsMap;
	std::unordered_map<size_t, EntityPairType> entitiesMap;

public:
	Mesh* loadMesh(const char* file);
	void releaseMesh(Mesh* mesh);
	Material* loadMaterial(const char* file);
	void releaseMaterial(Material* material);
	Entity* loadEntity(const char* file, std::string name);
	void releaseEntity(Entity* entity);

private:
	size_t generateKey(const char* input);

	void preRelease() override;
};

} // namespace
