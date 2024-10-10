#pragma once

#include "MeshData.h"

namespace sre
{

class MeshLoader
{
public:
	MeshData* load(const char* file);
};

} // namespace
