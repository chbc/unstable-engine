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
class ABaseMaterial;
class Texture;
struct ColorMeshData;

class AScene;

using ModelPairType		= std::pair<size_t, SPTR<Model>>;
using Model2DPairType	= std::pair<size_t, SPTR<Model2D>>;
using MaterialPairType	= std::pair<size_t, SPTR<ABaseMaterial>>;
using EntityPairType	= std::pair<size_t, SPTR<Entity>>;
using TexturePairType	= std::pair<size_t, SPTR<Texture>>;
using IconPairType		= std::pair<size_t, SPTR<Texture>>;
using GuizmoPairType	= std::pair<size_t, SPTR<ColorMeshData>>;

using ModelsMapType		= std::unordered_map<std::string, ModelPairType>;
using Models2DMapType	= std::unordered_map<std::string, Model2DPairType>;
using MaterialsMapType	= std::unordered_map<std::string, MaterialPairType>;
using EntitiesMapType	= std::unordered_map<std::string, EntityPairType>;
using TexturesMapType	= std::unordered_map<std::string, TexturePairType>;
using IconsMapType		= std::unordered_map<std::string, IconPairType>;
using GuizmosMapType	= std::unordered_map<std::string, GuizmoPairType>;

class SRE_API AssetsManager : public ASingleton
{
private:
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
	Model* loadModel(const std::string& filePath);
	MeshData* loadMesh(const char* filePath, const char* meshName);
	MeshData2D* loadMesh2D();
	void releaseModel(const char* filePath);
	void releaseModel2D(Model2D* model);
	ABaseMaterial* loadMaterial(const char* filePath);
	void releaseMaterial(ABaseMaterial* material);
	Texture* loadTexture(const char* filePath, ETextureMap::Type mapType);
	void releaseTexture(Texture* texture);
	Texture* loadIcon(const char* filePath);
	void releaseIcon(Texture* texture);
	ColorMeshData* loadGuizmo(EGuizmoMesh type);

protected:
	void preRelease() override;

private:
	template <typename TCollection, typename TLoader, typename TItem, typename... TArgs>
	TItem* loadAsset(TCollection& collection, const std::string& filePath, TArgs&&... parameters)
	{
		TItem* result = nullptr;

		std::string key{ filePath };
		if (collection.count(key) > 0)
		{
			auto& itemPair = collection[key];
			itemPair.first++;
			result = itemPair.second.get();
		}
		else
		{
			result = TLoader().load(filePath.c_str(), std::forward<TArgs>(parameters)...);
			collection.emplace(key, std::make_pair<std::size_t, SPTR<TItem>>(1, SPTR<TItem>{result}));
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

		std::string key = filePath;
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
};

} // namespace
