#include "MeshData.h"
#include "ModelLoader.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace sre;
namespace FS = std::filesystem;

void print(MeshData* mesh);
void saveMesh(MeshData* mesh, const char* fileName);

int main(int argc, const char* args[])
{
    if (argc != 2)
    {
        std::cout << "Usage: MeshConverter.exe [source_file]" << std::endl;
        system("pause");
        return 1;
    }

    std::vector<UPTR<MeshData>> meshes;
    ModelLoader().load(args[1], meshes);

    FS::path systemPath{ args[1] };
    std::string destFileName = systemPath.replace_extension(".mesh").string();

    for (size_t i = 0; i < meshes.size(); ++i)
    {
        MeshData* item = meshes[i].get();
        if (i == 0)
        {
            saveMesh(item, destFileName.c_str());
        }
        else
        {
            std::string fileName = destFileName.c_str() + i;
            saveMesh(item, fileName.c_str());
        }
    }

    return 0;
}

void saveMesh(MeshData* mesh, const char* fileName)
{
    size_t vertexSize = mesh->vertexData.size();
    size_t indicesSize = mesh->indices.size();

    std::string filePath{ fileName };

    std::ofstream saveStream(filePath, std::ios::out | std::ios::binary);
    if (saveStream)
    {
        saveStream.write(reinterpret_cast<const char*>(&vertexSize), sizeof(size_t));
        for (const VertexData& item : mesh->vertexData)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(VertexData));
        }

        saveStream.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
        for (const uint32_t& item : mesh->indices)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(uint16_t));
        }
    }
    saveStream.close();
}
