#include "MeshLoader.h"

#include <fstream>

namespace sre
{

MeshData* MeshLoader::load(const char* file)
{
	std::vector<VertexData> vertexData;
	std::vector<uint16_t> indices;
	std::ifstream readStream(file, std::ios::out | std::ios::binary);
	if (readStream)
	{
		size_t size;
		readStream.read((char*)&size, sizeof(size_t));
		for (size_t i = 0; i < size; i++)
		{
			VertexData item;
			readStream.read((char*)&item, sizeof(VertexData));
			vertexData.push_back(item);
		}

		readStream.read((char*)&size, sizeof(size_t));
		for (size_t i = 0; i < size; i++)
		{
			uint16_t item;
			readStream.read((char*)&item, sizeof(uint16_t));
			indices.push_back(item);
		}
	}

	readStream.close();

	MeshData* readMesh = new MeshData{ vertexData, indices };
	return readMesh;
}

} // namespace
