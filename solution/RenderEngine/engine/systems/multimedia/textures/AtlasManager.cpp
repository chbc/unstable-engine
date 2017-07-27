#include "AtlasManager.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

IMPLEMENT_SINGLETON(AtlasManager)

AtlasManager::AtlasManager() { }

void AtlasManager::init() { }

Atlas *AtlasManager::getAtlas(const std::string &fileName)
{
	Atlas *result = atlases[fileName].get();
	
	if (result == nullptr)
	{
		result = loadAtlas(fileName);
	}

	return result;
}

Atlas *AtlasManager::loadAtlas(const std::string &fileName)
{
	Atlas *result = nullptr;

	const std::string textureFile = fileName + ".png";
	const std::string fontFile = fileName + ".fnt";

	RenderManager *renderManager = RenderManager::getInstance();
	Texture *texture = renderManager->loadGUITexture(textureFile);

	result = new Atlas(texture);
	result->loadUVs(fontFile);

	return result;
}

void AtlasManager::release() { }

} // namespace
