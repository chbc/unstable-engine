#pragma once

#include <unordered_map>
#include <string>

#include "ASingleton.h"
#include "memory_aliases.h"

namespace sre
{

struct Mesh;
class Material;

using MeshPairType = std::pair<size_t, SPTR<Mesh>>;
using MaterialPairType = std::pair<size_t, SPTR<Material>>;

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	// <key, <ref count, mesh>
	std::unordered_map<size_t, MeshPairType> meshesMap;
	std::unordered_map<size_t, MaterialPairType> materialsMap;

public:
	Mesh* loadMesh(const char* file);
	void releaseMesh(Mesh* mesh);
	Material* loadMaterial(const char* file);
	void releaseMaterial(Material* material);

private:
	size_t generateKey(const char* input);

	void preRelease() override;
};

} // namespace
