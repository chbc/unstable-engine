#pragma once

#include "MeshData.h"
#include "memory_aliases.h"
#include <string>

namespace sre
{

struct Mesh
{
public:
	UPTR<AMeshData> meshData;

private:
	std::string filePath;

public:
	Mesh(AMeshData* arg_meshData, const char* arg_filePath);
	const std::string& getFilePath();

friend class AssetsManager;
};

} // namespace
