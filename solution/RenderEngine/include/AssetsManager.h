#pragma once

#include "Entity.h"
#include "ASingleton.h"
#include "memory_aliases.h"
#include "ETextureMap.h"

#include <unordered_map>
#include <string>

namespace sre
{

struct Mesh;
struct GUIMeshData;
class Material;
class Texture;

using MeshPairType		= std::pair<size_t, SPTR<Mesh>>;
using MaterialPairType	= std::pair<size_t, SPTR<Material>>;
using EntityPairType	= std::pair<size_t, SPTR<Entity>>;
using TexturePairType	= std::pair<size_t, SPTR<Texture>>;

using MeshesMapType		= std::unordered_map<size_t, MeshPairType>;
using MaterialsMapType	= std::unordered_map<size_t, MaterialPairType>;
using EntitiesMapType	= std::unordered_map<size_t, EntityPairType>;
using TexturesMapType	= std::unordered_map<size_t, TexturePairType>;

class AssetsManager : public ASingleton
{
private:
	std::hash<std::string> hash;
	// <key, <ref count, asset>
	MeshesMapType meshesMap;
	MaterialsMapType materialsMap;
	EntitiesMapType entitiesMap;
	TexturesMapType texturesMap;

public:
	Entity* loadEntity(const char* filePath, std::string name);
	void releaseEntity(Entity* entity);
	Mesh* loadMesh(const char* filePath);
	GUIMeshData* loadGUIMeshData();
	void releaseMesh(Mesh* mesh);
	Material* loadMaterial(const char* filePath);
	void releaseMaterial(Material* material);
	Texture* loadTexture(const char* filePath, ETextureMap::Type mapType);
	void releaseTexture(Texture* texture);

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
		if (collection.empty() || item->filePath.empty())
		{
			return;
		}

		size_t key = this->generateKey(item->filePath.c_str());
		if (collection.count(key) > 0)
		{
			auto& meshPair = collection[key];
			meshPair.first--;
			if (meshPair.first < 1)
			{
				if (releaseCallback != nullptr)
				{
					releaseCallback(item);
				}

				collection.erase(key);
			}
		}
	}

	size_t generateKey(const char* input);
};

} // namespace
