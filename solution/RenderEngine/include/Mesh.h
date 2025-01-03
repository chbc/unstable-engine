#pragma once

#include "MeshData.h"
#include "memory_aliases.h"
#include <string>

namespace sre
{

struct Mesh
{
	UPTR<AMeshData> meshData;
	std::string fileName;

public:
	Mesh(AMeshData* arg_meshData, const char* arg_fileName);

friend class MeshLoader;
};

} // namespace
