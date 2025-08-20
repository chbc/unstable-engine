#include "ModelLoader.h"
#include "MaterialSaver.h"
#include "FileUtils.h"

#include <fstream>
#include <filesystem>

#ifdef DEBUG
    #include <iostream>
#endif

using namespace sre;
namespace FS = std::filesystem;

void saveMesh(const MeshData& mesh, std::ofstream& saveStream);
void saveMaterial(const ModelImportData& modelData, const std::string& filePath);
void copyTextureFiles(const ModelImportData& modelData, const FS::path& sourcePath, const FS::path& destinationPath);

int main(int argc, const char* args[])
{
	if ((argc < 2) || (argc > 5))
    {
#ifdef DEBUG
        std::cout << "Usage: MeshConverter.exe [source_file] [destination_path] [scale_factor] [import_materials]" << std::endl;
#endif
        return 1;
    }

	float scaleFactor = (argc > 3) ? std::stof(args[3]) : 1.0f;
    bool importMaterials = (argc > 4) ? std::stoi(args[4]) : false;
    ModelImportData modelData;

    try
    {
		FileUtils::initializeStoragePaths();
        ModelLoader().load(args[1], scaleFactor, importMaterials, modelData);
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
        size_t meshesSize = modelData.meshes.size();

        // meshes size
        saveStream.write(reinterpret_cast<const char*>(&meshesSize), sizeof(size_t));

        // meshes
        for (const MeshData& item : modelData.meshes)
        {
            saveMesh(item, saveStream);
        }

        saveStream.close();

        // materials
        if (importMaterials)
        {
		    destinationPath = destinationPath.replace_extension("");
		    saveMaterial(modelData, destinationPath.string());
            copyTextureFiles(modelData, sourcePath.parent_path().string(), destinationPath.parent_path().string());
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

void saveMaterial(const ModelImportData& modelData, const std::string& filePath)
{
    MaterialSaver materialSaver;

    if (modelData.materials.size() == 1)
    {
		materialSaver.save(modelData.materials[0], filePath + ".mat");
    }
    else
    {
        size_t materialsSize = modelData.materials.size();
        std::vector<bool> savedIndices(materialsSize, false);

        for (const auto& meshMaterial : modelData.meshesMaterialMap)
        {
            int meshIndex = meshMaterial.second;
            if (!savedIndices[meshIndex])
            {
                savedIndices[meshIndex] = true;
                MaterialImportData materialData = modelData.materials[meshIndex];
                std::string resultPath = filePath + meshMaterial.first + ".mat";
                materialSaver.save(materialData, resultPath);
            }
        }
    }
}

void copyTextureFiles(const ModelImportData& modelData, const FS::path& sourcePath, const FS::path& destinationPath)
{
    for (const auto& material : modelData.materials)
    {
        for (const auto& texture : material.texturePaths)
        {
            FS::path resultSourcePath = sourcePath / FS::path{ texture.second };
            FS::path resultDestPath = destinationPath / FS::path{ texture.second };
            
			FS::path destinationBasePath = resultDestPath.parent_path();
            if (!FS::exists(destinationBasePath))
            {
				FS::create_directories(destinationBasePath);
			}

            FS::copy(resultSourcePath, resultDestPath, FS::copy_options::overwrite_existing);
        }
    }
}
