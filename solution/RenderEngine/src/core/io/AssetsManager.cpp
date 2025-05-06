#include "AssetsManager.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "EntityLoader.h"
#include "TextureLoader.h"
#include "SingletonsManager.h"
#include "Material.h"

namespace sre
{

Entity* AssetsManager::loadEntity(const char* filePath, std::string name)
{
	Entity* prototype = this->loadAsset<EntitiesMapType, EntityLoader, Entity>(this->entitiesMap, filePath, name);
	Entity* result = prototype->clone();
	result->name = name;

	return result;
}

void AssetsManager::releaseEntity(Entity* entity)
{
	this->releaseAsset(this->entitiesMap, entity);
}

MeshData* AssetsManager::loadMesh(const char* filePath, const char* meshName)
{
	Model* model = this->loadAsset<ModelsMapType, MeshLoader, Model>(this->modelsMap, filePath);
	MeshData* result = model->getMesh(meshName);
	return result;
}

MeshData2D* AssetsManager::loadMesh2D()
{
	const char* GUI_PLANE_PATH = "../content/engine/media/GUIPlane.mesh";
	Model2D* result = this->loadAsset<Models2DMapType, GUIMeshLoader, Model2D>(this->models2DMap, GUI_PLANE_PATH);
	return result->getMesh("Plane");
}

void AssetsManager::releaseModel(const char* filePath)
{
	std::function<void(Model*)> releaseCallback = [&](Model* item) { MeshLoader().release(item); };
	this->releaseAsset(this->modelsMap, filePath, releaseCallback);
}

void AssetsManager::releaseModel2D(Model2D* model)
{
	std::function<void(Model2D*)> releaseCallback = [&](Model2D* item) { GUIMeshLoader().release(item); };
	this->releaseAsset(this->models2DMap, model, releaseCallback);
}

Material* AssetsManager::loadMaterial(const char* filePath)
{
	Material* result = this->loadAsset<MaterialsMapType, MaterialLoader, Material>(this->materialsMap, filePath);
	return result;
}

void AssetsManager::releaseMaterial(Material* material)
{
	this->releaseAsset(this->materialsMap, material);
}

Texture* AssetsManager::loadTexture(const char* filePath, ETextureMap::Type mapType)
{
	Texture* result = this->loadAsset<TexturesMapType, TextureLoader, Texture>(this->texturesMap, filePath, mapType);
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

	// Models
	for (auto& it = this->modelsMap.begin(); it != this->modelsMap.end();)
	{
		MeshLoader().release((*it).second.second.get());
		it = this->modelsMap.erase(it);
	}

	// Models2D
	for (auto& it = this->models2DMap.begin(); it != this->models2DMap.end();)
	{
		GUIMeshLoader().release((*it).second.second.get());
		it = this->models2DMap.erase(it);
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
