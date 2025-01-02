#include "MeshData.h"
#include "ModelLoader.h"

#include <iostream>
#include <fstream>

using namespace sre;

void print(MeshData* mesh);
void saveMesh(MeshData* mesh, const char* fileName);

int main()
{
    std::vector<UPTR<MeshData>> meshes;
    ModelLoader().load("../../engine/media/viper/Viper.fbx", meshes);

    for (size_t i = 0; i < meshes.size(); ++i)
    {
        MeshData* item = meshes[i].get();
        if (i == 0)
        {
            saveMesh(item, "Viper.mesh");
        }
        else
        {
            std::string fileName = "Viper.mesh" + i;
            saveMesh(item, fileName.c_str());
        }
    }

    return 0;
}

void saveMesh(MeshData* mesh, const char* fileName)
{
    size_t vertexSize = mesh->vertexData.size();
    size_t indicesSize = mesh->indices.size();

    std::string filePath = std::string{ "../../engine/media/" } + fileName;

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

void print(MeshData* mesh)
{
    std::cout << "vertices" << std::endl;

    for (const VertexData& item : mesh->vertexData)
    {
        std::cout << "position: " << item.position.x << "\t" << item.position.y << "\t" << item.position.z << std::endl;
        std::cout << "normal: " << item.normal.x << "\t" << item.normal.y << "\t" << item.normal.z << "\t" << std::endl;
        std::cout << "UV: " << item.u << "\t" << item.v << std::endl;
        std::cout << std::endl;
    }

    std::cout << "indices" << std::endl;

    for (uint32_t item : mesh->indices)
    {
        std::cout << item << " ";
    }
}
