#include "MeshLoader.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

#include <fstream>

namespace sre
{

Mesh* MeshLoader::load(const char* filePath)
{
	return internalLoad<MeshData, VertexData>(filePath);
}

void MeshLoader::release(Mesh* mesh)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->deleteBuffers(mesh->meshData.get());
}

template <typename TMesh, typename TVertex>
Mesh* MeshLoader::internalLoad(const char* filePath)
{
	std::vector<TVertex> vertexData;
	std::vector<uint32_t> indices;
	std::ifstream readStream(filePath, std::ios::out | std::ios::binary);
	if (readStream)
	{
		size_t size;
		readStream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		vertexData.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			TVertex item;
			readStream.read(reinterpret_cast<char*>(&item), sizeof(TVertex));
			vertexData.push_back(item);
		}

		readStream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		indices.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			uint32_t item;
			readStream.read(reinterpret_cast<char*>(&item), sizeof(uint32_t));
			indices.push_back(item);
		}
	}

	readStream.close();

	TMesh* meshData = new TMesh{ vertexData, indices };
	Mesh* result = new Mesh{ meshData, filePath };
	return result;
}

Mesh* GIUMeshLoader::load(const char* filePath)
{
	return internalLoad<GUIMeshData, GUIVertexData>(filePath);
}

} // namespace
