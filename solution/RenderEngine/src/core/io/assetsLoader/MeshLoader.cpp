#include "MeshLoader.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "FileUtils.h"

#include <fstream>

namespace sre
{

template <typename TModel, typename TMesh, typename TVertex>
TModel* ABaseMeshLoader::internalLoad(const char* filePath)
{
	TModel* result = new TModel{ filePath };

	std::string absolutePath = FileUtils::getContentAbsolutePath(filePath);
	std::ifstream readStream(absolutePath, std::ios::out | std::ios::binary);
	if (readStream)
	{
		// meshes size
		size_t meshesSize = 0;
		readStream.read(reinterpret_cast<char*>(&meshesSize), sizeof(size_t));

		// meshes
		for (size_t i = 0; i < meshesSize; i++)
		{
			TMesh* mesh = this->loadMesh<TMesh, TVertex>(readStream);
			result->meshes.emplace(mesh->name, mesh);
		}
	}
	else
	{
		throw "[MeshLoader] - Error: " + std::string(filePath) + " can't be found!";
	}

	readStream.close();

	return result;
}

template <typename TModel, typename TMesh>
void ABaseMeshLoader::internalRelease(TModel* model)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	for (const auto& item : model->meshes)
	{
		graphicsWrapper->deleteBuffers(item.second.get());
	}
}

template<typename TMesh, typename TVertex>
TMesh* ABaseMeshLoader::loadMesh(std::ifstream& readStream)
{
	std::vector<TVertex> vertexData;
	std::vector<uint32_t> indices;
	std::string name;

	/*
	// begin mesh mark
	char mark;
	readStream.read(&mark, sizeof(size_t));
	*/

	// name size
	size_t nameSize = 0;
	readStream.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));

	// name
	if (nameSize > 0)
	{
		std::vector<char> buffer(nameSize);
		readStream.read(buffer.data(), nameSize);
		name = std::string(buffer.begin(), buffer.end());
	}

	// vertices size
	size_t verticesSize = 0;
	readStream.read(reinterpret_cast<char*>(&verticesSize), sizeof(size_t));

	// vertex data
	vertexData.reserve(verticesSize);
	for (size_t i = 0; i < verticesSize; i++)
	{
		TVertex item;
		readStream.read(reinterpret_cast<char*>(&item), sizeof(TVertex));
		vertexData.push_back(item);
	}

	// indices size
	size_t indicesSize = 0;
	readStream.read(reinterpret_cast<char*>(&indicesSize), sizeof(size_t));

	// indices
	indices.reserve(indicesSize);
	for (size_t i = 0; i < indicesSize; i++)
	{
		uint32_t item;
		readStream.read(reinterpret_cast<char*>(&item), sizeof(uint32_t));
		indices.push_back(item);
	}

	TMesh* result = new TMesh{ name, vertexData, indices };
	return result;
}

Model* MeshLoader::load(const char* filePath)
{
	return ABaseMeshLoader::internalLoad<Model, MeshData, VertexData>(filePath);
}

void MeshLoader::release(Model* model)
{
	ABaseMeshLoader::internalRelease<Model, MeshData>(model);
}

Model2D* GUIMeshLoader::load(const char* filePath)
{
	return ABaseMeshLoader::internalLoad<Model2D, MeshData2D, VertexData2D>(filePath);
}

void GUIMeshLoader::release(Model2D* model)
{
	ABaseMeshLoader::internalRelease<Model2D, MeshData2D>(model);
}

} // namespace
