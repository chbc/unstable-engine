#include "MeshData.h"
#include "ModelLoader.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace sre;
namespace FS = std::filesystem;

void saveMesh(const MeshData& mesh, std::ofstream& saveStream);

int main(int argc, const char* args[])
{
    if (argc != 2)
    {
        std::cout << "Usage: MeshConverter.exe [source_file]" << std::endl;
        system("pause");
        return 1;
    }

    std::vector<MeshData> meshes;
    ModelLoader().load(args[1], meshes);

    FS::path systemPath{ args[1] };
    std::string destFileName = systemPath.replace_extension(".mesh").string();

    std::string filePath{ destFileName };

    std::ofstream saveStream(filePath, std::ios::out | std::ios::binary);
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

    return 0;
}

void saveMesh(const MeshData& mesh, std::ofstream& saveStream)
{
    size_t verticesSize = mesh.vertexData.size();
    size_t indicesSize = mesh.indices.size();
    size_t nameSize = mesh.name.size();

    /*
    // begin mesh mark
    const char mark = 'M';
    saveStream.write(&mark, sizeof(size_t));
    */

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
