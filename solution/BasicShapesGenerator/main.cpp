#include "PrimitiveMeshFactory.h"
#include <iostream>
#include <fstream>

#define WRITE 1

using namespace sre;

void print(MeshData* mesh);
void saveMesh(MeshData* mesh, const char* fileName);

int main()
{
    PrimitiveMeshFactory meshFactory;
#if WRITE
    // WRITE
    /*
    MeshData* cubeMesh = meshFactory.createCube(1.0f);
    MeshData* planeMesh = meshFactory.createPlane(1.0f, 1.0f);
    */
    MeshData* sphereMesh = meshFactory.createSphere(1.0f);

    /*
    saveMesh(cubeMesh, "Cube.mesh");
    saveMesh(planeMesh, "Plane.mesh");
    */
    saveMesh(sphereMesh, "Sphere.mesh");

    /*
    delete cubeMesh;
    delete planeMesh;
    */

    delete sphereMesh;
    //
#else
    // READ

    MeshData* readMesh = meshFactory.load("Cube.Mesh");
    print(readMesh);

    delete readMesh;

    system("pause");
#endif
    //

    return 0;
}

void saveMesh(MeshData* mesh, const char* fileName)
{
    size_t vertexSize = mesh->vertexData.size();
    size_t indicesSize = mesh->indices.size();

    std::string filePath = std::string{ "../../media/" } + fileName;

    std::ofstream saveStream(filePath, std::ios::out | std::ios::binary);
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

    for (uint16_t item : mesh->indices)
    {
        std::cout << item << " ";
    }
}
