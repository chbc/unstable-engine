#include "AtlasManager.h"
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

void AtlasManager::release()
{
    this->atlases.clear();
}

Atlas *AtlasManager::getAtlas(const std::string &fileName)
{
	Atlas *result = this->atlases[fileName].get();

	if (result == nullptr)
	{
		result = loadAtlas(fileName);
	}

	return result;
}

Atlas *AtlasManager::loadAtlas(const std::string &baseFileName)
{
	Atlas *result;

	RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
	Texture *texture = renderManager->loadGUITexture(baseFileName + ".png");

	result = new Atlas{ texture };
	UPTR<Atlas> newItem{ result };
	result->load(baseFileName + ".atlas");
	this->atlases[baseFileName] = std::move(newItem);

	return result;
}

FontAtlas *AtlasManager::getFont(const std::string &fileName)
{
	FontAtlas *result = static_cast<FontAtlas *>(this->atlases[fileName].get());

	if (result == nullptr)
	{
		result = this->loadFont(fileName);
	}

	return result;
}

FontAtlas *AtlasManager::loadFont(const std::string &baseFileName)
{
	FontAtlas *result;

	RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
	Texture *texture = renderManager->loadGUITexture(baseFileName + ".png");

	result = new FontAtlas{ texture };
	UPTR<FontAtlas> newItem{ result };
	result->load(baseFileName + ".fnt");
	this->atlases[baseFileName] = std::move(newItem);

	return result;
}

} // namespace
