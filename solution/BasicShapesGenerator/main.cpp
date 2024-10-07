#include "PrimitiveMeshFactory.h"
#include <iostream>
#include <fstream>

#define WRITE 1


using namespace sre;

void print(MeshData* mesh);

int main()
{

#if WRITE
    // WRITE
    PrimitiveMeshFactory meshFactory;
    MeshData* mesh = meshFactory.createCube(1.0f);
    size_t vertexSize = mesh->vertexData.size();
    size_t indicesSize = mesh->indices.size();

    std::ofstream saveStream("Cube.mesh", std::ios::out | std::ios::binary);
    if (saveStream)
    {
        saveStream.write(reinterpret_cast<const char*>(&vertexSize), sizeof(size_t));
        for (const VertexData& item : mesh->vertexData)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(VertexData));
        }

        saveStream.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
        for (const uint16_t& item : mesh->indices)
        {
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(uint16_t));
        }
    }
    saveStream.close();
    delete mesh;
    //
#else
    // READ
    std::vector<VertexData> vertexData;
    std::vector<uint16_t> indices;
    std::ifstream readStream("Cube.mesh", std::ios::out | std::ios::binary);
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
    print(readMesh);

    delete readMesh;
#endif
    //

    return 0;
}

void print(MeshData* mesh)
{
    std::cout << "vertices" << std::endl;

    for (const VertexData& item : mesh->vertexData)
    {
        std::cout << item.position.x << "\t" << item.position.y << "\t" << item.position.z << std::endl;
    }

    std::cout << "indices" << std::endl;

    for (uint16_t item : mesh->indices)
    {
        std::cout << item << " ";
    }
}
