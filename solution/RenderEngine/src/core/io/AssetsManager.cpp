#include "AssetsManager.h"
#include "MeshLoader.h"
#include "RenderManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

Mesh* AssetsManager::loadMesh(const char* file)
{
	Mesh* result = nullptr;
	size_t key = generateKey(file);
	if (this->meshesMap.count(key) > 0)
	{
		MeshPairType& meshPair = this->meshesMap[key];
		meshPair.first++;
		result = meshPair.second.get();
	}
	else
	{
		result = MeshLoader().load(file);
		this->meshesMap.emplace(key, std::make_pair<size_t, UPTR<Mesh>>(1, UPTR<Mesh>{result}));
	}
	return result;
}

void AssetsManager::releaseMesh(Mesh* mesh)
{
	size_t key = this->generateKey(mesh->fileName.c_str());
	if (this->meshesMap.count(key) > 0)
	{
		MeshPairType& meshPair = this->meshesMap[key];
		meshPair.first--;
		if (meshPair.first < 1)
		{
			AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
			graphicsWrapper->deleteBuffers(mesh->meshData.get());
			this->meshesMap.erase(key);
		}
	}
}

size_t AssetsManager::generateKey(const char* input)
{
	return this->hash(std::string(input));
}

void AssetsManager::preRelease()
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();

	for (auto& item : this->meshesMap)
	{
		Mesh* mesh = item.second.second.get();
		graphicsWrapper->deleteBuffers(mesh->meshData.get());
	}
	this->meshesMap.clear();
}

} // namespace
