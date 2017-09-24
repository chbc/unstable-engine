#include "AtlasManager.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

IMPLEMENT_SINGLETON(AtlasManager)

AtlasManager::AtlasManager() { }

void AtlasManager::init() { }

Atlas *AtlasManager::getAtlas(const std::string &fileName)
{
	return this->getAtlas(fileName, ".png", ".atlas");
}

Atlas *AtlasManager::getFont(const std::string &fileName)
{
	return this->getAtlas(fileName, ".png", ".fnt");
}

Atlas *AtlasManager::getAtlas(const std::string &fileName, const std::string &textureExtension, const std::string &configExtension)
{
	Atlas *result = atlases[fileName].get();

	if (result == nullptr)
	{
		result = loadAtlas(fileName + textureExtension, fileName + configExtension);
	}

	return result;
}

Atlas *AtlasManager::loadAtlas(const std::string &textureFile, const std::string &configFile)
{
	Atlas *result = nullptr;

	RenderManager *renderManager = RenderManager::getInstance();
	Texture *texture = renderManager->loadGUITexture(textureFile);

	result = new Atlas(texture);
	result->load(configFile);

	return result;
}

void AtlasManager::release() 
{ 
	this->atlases.clear();
}

} // namespace
