#include "MeshLoader.h"
#include "Paths.h"

#include <fstream>

namespace sre
{

Mesh* MeshLoader::load(const char* file)
{
	std::vector<VertexData> vertexData;
	std::vector<uint32_t> indices;
	std::string filePath;
	Paths().buildMediaFilePath(EContentType::ENGINE, file, filePath);
	std::ifstream readStream(filePath, std::ios::out | std::ios::binary);
	if (readStream)
	{
		size_t size;
		readStream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		vertexData.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			VertexData item;
			readStream.read(reinterpret_cast<char*>(&item), sizeof(VertexData));
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

	MeshData* meshData = new MeshData{ vertexData, indices };
	Mesh* result = new Mesh{ meshData, file };
	return result;
}

} // namespace
