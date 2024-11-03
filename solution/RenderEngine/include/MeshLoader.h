#pragma once

#include "Mesh.h"

namespace sre
{

class MeshLoader
{
public:
	Mesh* load(const char* file);
};

} // namespace
