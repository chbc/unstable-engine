#include "MeshData.h"
#include "ModelLoader.h"

#include <fstream>
#include <filesystem>

using namespace sre;
namespace FS = std::filesystem;

void saveMesh(const MeshData& mesh, std::ofstream& saveStream);

int main(int argc, const char* args[])
{
	if ((argc < 2) || (argc > 4))
    {
        return 1;
    }

	float scaleFactor = (argc > 3) ? std::stof(args[3]) : 1.0f;
    std::vector<MeshData> meshes;

    try
    {
        ModelLoader().load(args[1], scaleFactor, meshes);
    }
    catch (...)
    {
        return 1;
    }

    FS::path sourcePath{ args[1] };
    FS::path destinationPath = sourcePath.parent_path();
    FS::path fileName = sourcePath.filename().replace_extension(".mesh");

    if (argc > 2)
    {
		destinationPath = FS::path{ args[2] } / fileName;
    }

	int result = 0;
    std::ofstream saveStream(destinationPath, std::ios::out | std::ios::binary);
    if (saveStream)
    {
        size_t meshesSize = meshes.size();

        // meshes size
        saveStream.write(reinterpret_cast<const char*>(&meshesSize), sizeof(size_t));

        // meshes
        for (const MeshData& item : meshes)
        {
            saveMesh(item, saveStream);
        }
    }
	else
	{
		result = 1;
	}

    return result;
}

void saveMesh(const MeshData& mesh, std::ofstream& saveStream)
{
    size_t verticesSize = mesh.vertexData.size();
    size_t indicesSize = mesh.indices.size();
    size_t nameSize = mesh.name.size();

    // name size
    saveStream.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));

    // name
    if (nameSize > 0)
    {
        saveStream.write(mesh.name.c_str(), nameSize);
    }

    // vertices size
    saveStream.write(reinterpret_cast<const char*>(&verticesSize), sizeof(size_t));

    // vertex data
    if (verticesSize > 0)
    {
        for (const VertexData& item : mesh.vertexData)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(VertexData));
        }
    }

    // indices size
    saveStream.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));

    // indices
    if (indicesSize > 0)
    {
        for (const uint32_t& item : mesh.indices)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(uint32_t));
        }
    }
}
