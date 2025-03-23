#include "AtlasManager.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

namespace sre
{

void AtlasManager::release()
{
    this->atlases.clear();
}

Atlas* AtlasManager::getAtlas(const std::string &filePath)
{
	Atlas *result = this->atlases[filePath].get();

	if (result == nullptr)
	{
		result = loadAtlas(filePath);
	}

	return result;
}

Atlas* AtlasManager::loadAtlas(const std::string &baseFileName)
{
	Atlas *result;

	Texture* texture = this->loadTexture(baseFileName);

	result = new Atlas{ texture };
	UPTR<Atlas> newItem{ result };
	result->load(baseFileName + ".atlas");
	this->atlases[baseFileName] = std::move(newItem);

	return result;
}

FontAtlas* AtlasManager::getFont(const std::string &filePath)
{
	FontAtlas *result = static_cast<FontAtlas *>(this->atlases[filePath].get());

	if (result == nullptr)
	{
		result = this->loadFont(filePath);
	}

	return result;
}

FontAtlas* AtlasManager::loadFont(const std::string &baseFileName)
{
	FontAtlas *result;

	Texture* texture = this->loadTexture(baseFileName);

	result = new FontAtlas{ texture };
	UPTR<FontAtlas> newItem{ result };
	result->load(baseFileName + ".fnt");
	this->atlases[baseFileName] = std::move(newItem);

	return result;
}

Texture* AtlasManager::loadTexture(const std::string& baseFileName)
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	std::string filePath = baseFileName + ".png";
	return assetsManager->loadTexture(filePath.c_str(), ETextureMap::GUI);
}

} // namespace
