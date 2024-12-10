#pragma once

#include "Material.h"

namespace sre
{

class MaterialLoader
{
public:
	void save(Material* material, const char* name);
	Material* load(const char* fileName);
};

} // namespace
