#include "MeshLoader.h"

#include <fstream>

namespace sre
{
#ifdef __ANDROID__
	const std::string BASE_FOLDER = "media/es/";
#else
	const std::string BASE_FOLDER = "../../media/";
#endif

Mesh* MeshLoader::load(const char* file)
{
	std::vector<VertexData> vertexData;
	std::vector<uint16_t> indices;
	std::string filePath = BASE_FOLDER + file;
	std::ifstream readStream(filePath, std::ios::out | std::ios::binary);
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

	MeshData* meshData = new MeshData{ vertexData, indices };
	Mesh* result = new Mesh{ meshData, file };
	return result;
}

} // namespace
