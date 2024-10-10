#include "AssetsManager.h"
#include "MeshLoader.h"

namespace sre
{

MeshData* AssetsManager::loadMesh(const char* file)
{
	size_t key = generateKey(file);

	MeshData* result;
	
	if (this->meshesMap.count(key) > 0)
	{
		result = this->meshesMap[key].get();
	}
	else
	{
		result = MeshLoader().load(file);
		this->meshesMap.emplace(key, result);
	}
	
	return result;
}

size_t AssetsManager::generateKey(const char* input)
{
	return this->hash(std::string(input));
}

} // namespace
