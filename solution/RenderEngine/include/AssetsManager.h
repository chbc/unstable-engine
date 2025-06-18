#pragma once

#include "Entity.h"
#include "ASingleton.h"
#include "memory_aliases.h"
#include "ETextureMap.h"
#include "EGuizmoMesh.h"

#include <unordered_map>
#include <string>

namespace sre
{

struct Model;
struct Model2D;
struct MeshData;
struct MeshData2D;
class Material;
class Texture;
class ColorMeshData;

class AScene;

using ModelPairType		= std::pair<size_t, SPTR<Model>>;
using Model2DPairType	= std::pair<size_t, SPTR<Model2D>>;
using MaterialPairType	= std::pair<size_t, SPTR<Material>>;
using EntityPairType	= std::pair<size_t, SPTR<Entity>>;
using TexturePairType	= std::pair<size_t, SPTR<Texture>>;
using IconPairType		= std::pair<size_t, SPTR<Texture>>;
using GuizmoPairType	= std::pair<size_t, SPTR<ColorMeshData>>;

using ModelsMapType		= std::unordered_map<size_t, ModelPairType>;
using Models2DMapType	= std::unordered_map<size_t, Model2DPairType>;
using MaterialsMapType	= std::unordered_map<size_t, MaterialPairType>;
using EntitiesMapType	= std::unordered_map<size_t, EntityPairType>;
using TexturesMapType	= std::unordered_map<size_t, TexturePairType>;
using IconsMapType		= std::unordered_map<size_t, IconPairType>;
using GuizmosMapType	= std::unordered_map<size_t, GuizmoPairType>;

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	// <key, <ref count, asset>
	ModelsMapType modelsMap;
	Models2DMapType models2DMap;
	MaterialsMapType materialsMap;
	EntitiesMapType entitiesMap;
	TexturesMapType texturesMap;
	IconsMapType iconsMap;
	GuizmosMapType guizmosMap;

public:
	Entity* loadEntity(AScene* scene, const char* filePath, std::string name);
	void releaseEntity(Entity* entity);
	Model* loadModel(const char* filePath);
	MeshData* loadMesh(const char* filePath, const char* meshName);
	MeshData2D* loadMesh2D();
	void releaseModel(const char* filePath);
	void releaseModel2D(Model2D* model);
	Material* loadMaterial(const char* filePath);
	void releaseMaterial(Material* material);
	Texture* loadTexture(const char* filePath, ETextureMap::Type mapType);
	void releaseTexture(Texture* texture);
	Texture* loadIcon(const char* filePath);
	void releaseIcon(Texture* texture);
	ColorMeshData* loadGuizmo(EGuizmoMesh type);

protected:
	void preRelease() override;

private:
	template <typename TCollection, typename TLoader, typename TItem, typename... TArgs>
	TItem* loadAsset(TCollection& collection, const char* filePath, TArgs&&... parameters)
	{
		TItem* result = nullptr;

		size_t key = generateKey(filePath);
		if (collection.count(key) > 0)
		{
			auto& itemPair = collection[key];
			itemPair.first++;
			result = itemPair.second.get();
		}
		else
		{
			result = TLoader().load(filePath, std::forward<TArgs>(parameters)...);
			collection.emplace(key, std::make_pair<size_t, SPTR<TItem>>(1, SPTR<TItem>{result}));
		}

		return result;
	}

	template <typename TCollection, typename TItem>
	void releaseAsset(TCollection& collection, TItem* item, std::function<void(TItem*)> releaseCallback = nullptr)
	{
		this->releaseAsset(collection, item->filePath, releaseCallback);
	}

	template <typename TCollection, typename TItem>
	void releaseAsset(TCollection& collection, const std::string& filePath, std::function<void(TItem*)> releaseCallback = nullptr)
	{
		if (collection.empty() || filePath.empty())
		{
			return;
		}

		size_t key = this->generateKey(filePath.c_str());
		if (collection.count(key) > 0)
		{
			auto& assetPair = collection[key];
			assetPair.first--;
			if (assetPair.first < 1)
			{
				if (releaseCallback != nullptr)
				{
					releaseCallback(assetPair.second.get());
				}

				collection.erase(key);
			}
		}
	}

	size_t generateKey(const char* input);
};

} // namespace
