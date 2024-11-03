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
	Mesh(AMeshData* arg_meshData, const char* arg_fileName) : fileName(arg_fileName)
	{
		meshData.reset(arg_meshData);
	}

friend class MeshLoader;
};

} // namespace
