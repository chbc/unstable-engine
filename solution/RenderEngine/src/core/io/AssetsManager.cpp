#include "AssetsManager.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "EntityLoader.h"
#include "TextureLoader.h"
#include "GuizmoLoader.h"
#include "SingletonsManager.h"
#include "Material.h"

namespace sre
{

Entity* AssetsManager::loadEntity(AScene* scene, const char* filePath, std::string name)
{
	Entity* prototype = this->loadAsset<EntitiesMapType, EntityLoader, Entity>(this->entitiesMap, filePath, name, scene);
	Entity* result = prototype->clone();
	result->name = name;

	return result;
}

void AssetsManager::releaseEntity(Entity* entity)
{
	this->releaseAsset(this->entitiesMap, entity);
}

Model* AssetsManager::loadModel(const char* filePath)
{
	Model* result = this->loadAsset<ModelsMapType, MeshLoader, Model>(this->modelsMap, filePath);
	return result;
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

Texture* AssetsManager::loadIcon(const char* filePath)
{
	Texture* result = this->loadAsset<IconsMapType, TextureLoader, Texture>(this->iconsMap, filePath, ETextureMap::GUI);
	return result;
}

void AssetsManager::releaseIcon(Texture* texture)
{
	std::function<void(Texture*)> releaseCallback = [&](Texture* item) { TextureLoader().release(item); };
	this->releaseAsset(this->iconsMap, texture, releaseCallback);
}

ColorMeshData* AssetsManager::loadGuizmo(EGuizmoMesh type)
{
	std::string guizmoPath;
	switch (type)
	{
		case EGuizmoMesh::Box:
			guizmoPath = "BOX";
			break;
		case EGuizmoMesh::Sphere:
			guizmoPath = "SPHERE";
			break;
		case EGuizmoMesh::SunRays:
			guizmoPath = "SUN_RAYS";
			break;
		default: break;
	}

	ColorMeshData* result = this->loadAsset<GuizmosMapType, GuizmoLoader, ColorMeshData>(this->guizmosMap, guizmoPath.c_str());
	return result;
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

	// Icons
	for (auto& it = this->iconsMap.begin(); it != this->iconsMap.end();)
	{
		TextureLoader().release((*it).second.second.get());
		it = this->iconsMap.erase(it);
	}

	// Guizmos
	for (auto& it = this->guizmosMap.begin(); it != this->guizmosMap.end();)
	{
		GuizmoLoader().release((*it).second.second.get());
		it = this->guizmosMap.erase(it);
	}
}

size_t AssetsManager::generateKey(const char* input)
{
	return this->hash(std::string(input));
}

} // namespace
