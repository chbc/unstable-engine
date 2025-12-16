#include "AssetsManager.h"
#include "EntityLoader.h"
#include "MeshLoader.h"
#include "MaterialLoader.h"
#include "TextureLoader.h"
#include "GuizmoLoader.h"
#include "Entity.h"
#include "ABaseMaterial.h"
#include "FileUtils.h"

namespace sre
{

Entity* AssetsManager::loadEntity(AScene* scene, const char* filePath, std::string name)
{
	std::string relativePath = FileUtils::getContentRelativePath(filePath);

	const auto& loadFunction = [&]()
	{
		return EntityLoader().load(relativePath.c_str(), name, scene);
	};
	
	AAsset* prototype = this->entitiesCollection.loadAsset(relativePath, loadFunction);
	Entity* prototypeEntity = static_cast<Entity*>(prototype);
	Entity* result = prototypeEntity->clone();
	result->name = name;

	return result;
}

Model* AssetsManager::loadModel(const std::string& filePath)
{
	std::string relativePath = FileUtils::getContentRelativePath(filePath);
	const auto& loadFunction = [&]()
	{
		return MeshLoader().load(relativePath.c_str());
	};

	Model* result = static_cast<Model*>(this->modelsCollection.loadAsset(relativePath, loadFunction));

	size_t meshCount = result->getMeshCount();
	if (meshCount > 1)
	{
		this->modelsCollection.increaseReferences(relativePath, meshCount - 1);
	}

	return result;
}

MeshData* AssetsManager::loadMesh(const char* filePath, const char* meshName)
{
	Model* model = this->loadModel(filePath);
	MeshData* result = model->getMesh(meshName);
	return result;
}

MeshData2D* AssetsManager::loadMesh2D()
{
	const char* GUI_PLANE_PATH = "../content/engine/media/GUIPlane.mesh";
	const auto& loadFunction = [&]()
	{
		return GUIMeshLoader().load(GUI_PLANE_PATH);
	};

	Model2D* result = static_cast<Model2D*>(this->models2DCollection.loadAsset(GUI_PLANE_PATH, loadFunction));
	return result->getMesh("Plane");
}

ABaseMaterial* AssetsManager::loadMaterial(const std::string& filePath, size_t referencesCount)
{
	std::string relativePath = FileUtils::getContentRelativePath(filePath);
	const auto& loadFunction = [&]()
	{
		return MaterialLoader().load(relativePath.c_str());
	};

	ABaseMaterial* result = static_cast<ABaseMaterial*>(this->materialsCollection.loadAsset(relativePath, loadFunction));
	if (referencesCount > 1)
	{
		this->materialsCollection.increaseReferences(relativePath, referencesCount - 1);
	}

	return result;
}

Texture* AssetsManager::loadTexture(const char* filePath, ETextureMap::Type mapType)
{
	std::string relativePath = FileUtils::getContentRelativePath(filePath);
	const auto& loadFunction = [&]()
	{
		return TextureLoader().load(filePath, mapType);
	};

	Texture* result = static_cast<Texture*>(this->texturesCollection.loadAsset(relativePath, loadFunction));
	return result;
}

Texture* AssetsManager::loadIcon(const char* filePath)
{
	std::string relativePath = FileUtils::getContentRelativePath(filePath);
	const auto& loadFunction = [&]()
	{
		return TextureLoader().load(filePath, ETextureMap::GUI);
	};

	Texture* result = static_cast<Texture*>(this->iconsCollection.loadAsset(relativePath, loadFunction));
	return result;
}

ColorMeshData* AssetsManager::loadGuizmo(EGuizmoMesh type)
{
	ColorMeshData* result{ nullptr };

	if (this->guizmosCollection.count(type) > 0)
	{
		result = this->guizmosCollection[type].get();
	}
	else
	{
		result = GuizmoLoader().load(type);
		this->guizmosCollection[type] = UPTR<ColorMeshData>{ result };
	}

	return result;
}

void AssetsManager::releaseEntity(Entity* entity)
{
	this->entitiesCollection.releaseAsset(entity->getFilePath());
}

void AssetsManager::releaseModel(const char* filePath)
{
	const auto& releaseCallback = [&](AAsset* item)
	{
		MeshLoader().release(static_cast<Model*>(item));
	};
	this->modelsCollection.releaseAsset(filePath, releaseCallback);
}

void AssetsManager::releaseModel2D(Model2D* model)
{
	const auto& releaseCallback = [&](AAsset* item)
	{
		GUIMeshLoader().release(static_cast<Model2D*>(item));
	};
	this->models2DCollection.releaseAsset(model->getFilePath(), releaseCallback);
}

void AssetsManager::releaseMaterial(ABaseMaterial* material)
{
	this->materialsCollection.releaseAsset(material->getFilePath());
}

void AssetsManager::releaseTexture(Texture* texture)
{
	const auto& releaseCallback = [&](AAsset* item)
	{
		TextureLoader().release(static_cast<Texture*>(item));
	};
	this->texturesCollection.releaseAsset(texture->getFilePath(), releaseCallback);
}

void AssetsManager::releaseIcon(Texture* texture)
{
	const auto& releaseCallback = [&](AAsset* item)
	{
		TextureLoader().release(static_cast<Texture*>(item));
	};
	this->iconsCollection.releaseAsset(texture->getFilePath(), releaseCallback);
}

void AssetsManager::preRelease()
{
	// Entities
	this->entitiesCollection.clear();

	// Models
	this->modelsCollection.clear([&](AAsset* asset)
	{
		Model* modelAsset = static_cast<Model*>(asset);
		MeshLoader().release(modelAsset);
	});

	// Models2D
	this->models2DCollection.clear([&](AAsset* asset)
	{
		Model2D* model2DAsset = static_cast<Model2D*>(asset);
		GUIMeshLoader().release(model2DAsset);
	});

	// Materials
	this->materialsCollection.clear();

	// Textures
	this->texturesCollection.clear([&](AAsset* asset)
	{
		Texture* textureAsset = static_cast<Texture*>(asset);
		TextureLoader().release(textureAsset);
	});

	// Icons
	this->iconsCollection.clear([&](AAsset* asset)
	{
		Texture* iconAsset = static_cast<Texture*>(asset);
		TextureLoader().release(iconAsset);
	});

	// Guizmos
	for (const auto& it : this->guizmosCollection)
	{
		GuizmoLoader().release(it.second.get());
	}

	this->guizmosCollection.clear();
}

} // namespace
