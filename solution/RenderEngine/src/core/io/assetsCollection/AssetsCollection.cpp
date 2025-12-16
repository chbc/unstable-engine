#include "AssetsCollection.h"

namespace sre
{

AAsset* AssetsCollection::loadAsset(const std::string& filePath, const std::function<AAsset*(void)>& loadFunction)
{
	AAsset* result = nullptr;
	std::string key{ filePath };
	if (this->assetsMap.count(key) > 0)
	{
		auto& itemPair = this->assetsMap[key];
		itemPair.first++;
		result = itemPair.second.get();
	}
	else
	{
		result = loadFunction();
		this->assetsMap.emplace(key, std::make_pair<std::size_t, SPTR<AAsset>>(1, SPTR<AAsset>{result}));
	}
	return result;
}

void AssetsCollection::releaseAsset(const std::string& filePath, const std::function<void(AAsset*)>& releaseCallback)
{
	if (this->assetsMap.empty() || filePath.empty())
	{
		return;
	}

	std::string key = filePath;
	if (this->assetsMap.count(key) > 0)
	{
		auto& assetPair = this->assetsMap[key];
		assetPair.first--;
		if (assetPair.first < 1)
		{
			if (releaseCallback != nullptr)
			{
				releaseCallback(assetPair.second.get());
			}
			this->assetsMap.erase(key);
		}
	}
}

void AssetsCollection::increaseReferences(const std::string& filePath, size_t referencesCount)
{
	if (this->assetsMap.count(filePath) > 0)
	{
		auto& assetPair = this->assetsMap[filePath];
		assetPair.first += referencesCount;
	}
}

void AssetsCollection::clear(const std::function<void(AAsset*)>& releaseCallback)
{
	if (releaseCallback)
	{
		for (auto& it = this->assetsMap.begin(); it != this->assetsMap.end();)
		{
			if (releaseCallback != nullptr)
			{
				releaseCallback(it->second.second.get());
			}
			it = this->assetsMap.erase(it);
		}
	}
	else
	{
		this->assetsMap.clear();
	}
}

} // namespace
