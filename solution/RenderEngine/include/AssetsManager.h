#pragma once

#include <unordered_map>
#include <string>

#include "ASingleton.h"
#include "Mesh.h"

namespace sre
{

using MeshPairType = std::pair<size_t, UPTR<Mesh>>;

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	// <key, <ref count, mesh>
	std::unordered_map<size_t, MeshPairType> meshesMap;

public:
	Mesh* loadMesh(const char* file);
	void releaseMesh(Mesh* mesh);

private:
	size_t generateKey(const char* input);

	void preRelease() override;
};

} // namespace
