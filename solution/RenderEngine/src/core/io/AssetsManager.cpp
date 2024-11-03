#include "AssetsManager.h"
#include "MeshLoader.h"

namespace sre
{

Mesh* AssetsManager::loadMesh(const char* file)
{
	size_t key = generateKey(file);

	Mesh* result;
	
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

void AssetsManager::release()
{
	for (auto& item : this->meshesMap)
	{
		item.second.reset();
	}

	this->meshesMap.clear();
}

} // namespace
