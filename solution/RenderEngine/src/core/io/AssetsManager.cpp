#include "AssetsManager.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "EntityLoader.h"
#include "TextureLoader.h"
#include "SingletonsManager.h"
#include "Material.h"

namespace sre
{

Entity* AssetsManager::loadEntity(const char* fileName, std::string name)
{
	Entity* prototype = this->loadAsset<EntitiesMapType, EntityLoader, Entity>(this->entitiesMap, fileName, name);
	Entity* result = prototype->clone();
	result->name = name;

	return result;
}

void AssetsManager::releaseEntity(Entity* entity)
{
	this->releaseAsset(this->entitiesMap, entity);
}

Mesh* AssetsManager::loadMesh(const char* fileName)
{
	Mesh* result = this->loadAsset<MeshesMapType, MeshLoader, Mesh>(this->meshesMap, fileName);
	return result;
}

GUIMeshData* AssetsManager::loadGUIMeshData()
{
	Mesh* result = this->loadAsset<MeshesMapType, GIUMeshLoader, Mesh>(this->meshesMap, "GUIPlane.mesh");
	return static_cast<GUIMeshData*>(result->meshData.get());
}

void AssetsManager::releaseMesh(Mesh* mesh)
{
	std::function<void(Mesh*)> releaseCallback = [&](Mesh* item) { MeshLoader().release(item); };
	this->releaseAsset(this->meshesMap, mesh, releaseCallback);
}

Material* AssetsManager::loadMaterial(const char* fileName)
{
	Material* result = this->loadAsset<MaterialsMapType, MaterialLoader, Material>(this->materialsMap, fileName);
	return result;
}

void AssetsManager::releaseMaterial(Material* material)
{
	this->releaseAsset(this->materialsMap, material);
}

Texture* AssetsManager::loadTexture(const char* fileName, ETextureMap::Type mapType)
{
	Texture* result = this->loadAsset<TexturesMapType, TextureLoader, Texture>(this->texturesMap, fileName, mapType);
	return result;
}

Texture* AssetsManager::loadIcon(const char* fileName)
{
	Texture* result = this->loadAsset<TexturesMapType, IconLoader, Texture>(this->texturesMap, fileName, ETextureMap::GUI);
	return result;
}

void AssetsManager::releaseTexture(Texture* texture)
{
	std::function<void(Texture*)> releaseCallback = [&](Texture* item) { TextureLoader().release(item); };
	this->releaseAsset(this->texturesMap, texture, releaseCallback);
}

void AssetsManager::preRelease()
{
	// Entities
	this->entitiesMap.clear();

	// Meshes
	for (auto& it = this->meshesMap.begin(); it != this->meshesMap.end();)
	{
		MeshLoader().release((*it).second.second.get());
		it = this->meshesMap.erase(it);
	}

	// Materials
	this->materialsMap.clear();

	// Textures
	for (auto& it = this->texturesMap.begin(); it != this->texturesMap.end();)
	{
		TextureLoader().release((*it).second.second.get());
		it = this->texturesMap.erase(it);
	}
}

size_t AssetsManager::generateKey(const char* input)
{
	return this->hash(std::string(input));
}

} // namespace
