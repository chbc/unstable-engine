#pragma once

#include "MeshData.h"
#include "ETextureMap.h"

#include <unordered_map>

namespace sre
{

struct MaterialImportData
{
	std::unordered_map<ETextureMap::Type, std::string> texturePaths;

	static const char* getTypeString(ETextureMap::Type type)
	{
		switch(type)
		{
			case ETextureMap::DIFFUSE: return "Albedo";
			case ETextureMap::NORMAL: return "Normal";
			case ETextureMap::AMBIENT_OCCLUSION: return "Ambient Occlusion";
			case ETextureMap::METALLIC: return "Metallic";
			case ETextureMap::ROUGHNESS: return "Roughness";
			default: return nullptr;
		}
	}
};

struct ModelImportData
{
	std::vector<MeshData> meshes;
	std::vector<MaterialImportData> materials;
	std::unordered_map<std::string, int> meshesMaterialMap;
};

} // namespace
