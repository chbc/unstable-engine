#include "MeshLoader.h"
#include "Paths.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

#include <fstream>

namespace sre
{

Mesh* MeshLoader::load(const char* fileName)
{
	return internalLoad<MeshData, VertexData>(fileName);
}

void MeshLoader::release(Mesh* mesh)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->deleteBuffers(mesh->meshData.get());
}

template <typename TMesh, typename TVertex>
Mesh* MeshLoader::internalLoad(const char* fileName)
{
	std::vector<TVertex> vertexData;
	std::vector<uint32_t> indices;
	std::string filePath;
	Paths().buildMediaFilePath(fileName, filePath);
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
	Mesh* result = new Mesh{ meshData, filePath.c_str()};
	return result;
}

Mesh* GIUMeshLoader::load(const char* fileName)
{
	return internalLoad<GUIMeshData, GUIVertexData>(fileName);
}

} // namespace
