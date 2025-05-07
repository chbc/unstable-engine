#include "PrimitiveMeshFactory.h"

#include <iostream>
#include <fstream>

using namespace sre;

template <typename TMesh, typename TVertex>
void saveMesh(TMesh* mesh, const std::string& name, const char* fileName);

int main()
{
    PrimitiveMeshFactory meshFactory;
    MeshData* cubeMesh = meshFactory.createCube(1.0f);
    MeshData* planeMesh = meshFactory.createPlane(1.0f, 1.0f);
    MeshData* sphereMesh = meshFactory.createSphere(1.0f);
    MeshData2D* guiMesh = meshFactory.createPlaneTopDown(glm::vec2{ 1.0f, 1.0f });

    saveMesh<MeshData, VertexData>(cubeMesh, "Cube", "Cube.mesh");
    saveMesh<MeshData, VertexData>(planeMesh, "Plane", "Plane.mesh");
    saveMesh<MeshData, VertexData>(sphereMesh, "Sphere", "Sphere.mesh");
    saveMesh<MeshData2D, VertexData2D>(guiMesh, "Plane", "GUIPlane.mesh");

    delete cubeMesh;
    delete planeMesh;
    delete sphereMesh;
    delete guiMesh;

    return 0;
}

template <typename TMesh, typename TVertex>
void saveMesh(TMesh* mesh, const std::string& name, const char* fileName)
{
    size_t verticesSize = mesh->vertexData.size();
    size_t indicesSize = mesh->indices.size();
    size_t nameSize = name.size();

    std::string filePath = std::string{ "../content/engine/media/" } + fileName;

    std::ofstream saveStream(filePath, std::ios::out | std::ios::binary);
    if (saveStream)
    {
        // meshes size
        size_t meshesSize = 1;
        saveStream.write(reinterpret_cast<const char*>(&meshesSize), sizeof(size_t));

        // name size
        saveStream.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));

        // name
        saveStream.write(name.c_str(), nameSize);

        // vertices size
        saveStream.write(reinterpret_cast<const char*>(&verticesSize), sizeof(size_t));
        for (const TVertex& item : mesh->vertexData)
        {
            // vertex data
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(TVertex));
        }

        // indices size
        saveStream.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
        for (const uint32_t& item : mesh->indices)
        {
            // indices
            saveStream.write(reinterpret_cast<const char*>(&item), sizeof(uint32_t));
        }
    }
    saveStream.close();
}
