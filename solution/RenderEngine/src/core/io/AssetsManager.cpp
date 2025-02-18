#include "AssetsManager.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "EntityLoader.h"
#include "TextureLoader.h"
#include "SingletonsManager.h"
#include "Material.h"

namespace sre
{

Entity* AssetsManager::loadEntity(const char* file, std::string name)
{
	Entity* prototype = this->loadAsset<EntitiesMapType, EntityLoader, Entity>(this->entitiesMap, file, name);
	Entity* result = prototype->clone();

	return result;
}

void AssetsManager::releaseEntity(Entity* entity)
{
	this->releaseAsset(this->entitiesMap, entity);
}

Mesh* AssetsManager::loadMesh(const char* file)
{
	Mesh* result = this->loadAsset<MeshesMapType, MeshLoader, Mesh>(this->meshesMap, file);
	return result;
}

void AssetsManager::releaseMesh(Mesh* mesh)
{
	std::function<void(Mesh*)> releaseCallback = [&](Mesh* item) { MeshLoader().release(item); };
	this->releaseAsset(this->meshesMap, mesh, releaseCallback);
}

Material* AssetsManager::loadMaterial(const char* file)
{
	Material* result = this->loadAsset<MaterialsMapType, MaterialLoader, Material>(this->materialsMap, file);
	return result;
}

void AssetsManager::releaseMaterial(Material* material)
{
	this->releaseAsset(this->materialsMap, material);
}

Texture* AssetsManager::loadTexture(const char* file, ETextureMap::Type mapType)
{
	Texture* result = this->loadAsset<TexturesMapType, TextureLoader, Texture>(this->texturesMap, file, mapType);
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
