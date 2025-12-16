#pragma once

#include "AAsset.h"
#include "memory_aliases.h"

#include <unordered_map>
#include <functional>

namespace sre
{

class AssetsCollection
{
protected:
	std::unordered_map<std::string, std::pair<std::size_t, SPTR<AAsset>>> assetsMap;

protected:
	virtual AAsset* loadAsset(const std::string& filePath, const std::function<AAsset*(void)>& loadFunction);
	virtual void releaseAsset(const std::string& filePath, const std::function<void(AAsset*)>& releaseCallback = nullptr);
	void increaseReferences(const std::string& filePath, size_t referencesCount);
	void clear(const std::function<void(AAsset*)>& releaseCallback = nullptr);

friend class AssetsManager;
};

} // namespace
