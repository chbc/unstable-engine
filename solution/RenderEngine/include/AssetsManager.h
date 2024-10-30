#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "ASingleton.h"
#include "MeshData.h"

namespace sre
{

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	std::unordered_map<size_t, std::unique_ptr<MeshData>> meshesMap;

public:
	MeshData* loadMesh(const char* file);

private:
	size_t generateKey(const char* input);

	void release() override;
};

} // namespace
