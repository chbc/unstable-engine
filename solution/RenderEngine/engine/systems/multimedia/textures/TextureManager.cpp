#include "TextureManager.h"
#include <exception>
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

TextureManager::TextureManager(AGraphicsWrapper *graphicsWrapper)
{
	this->graphicsWrapper = graphicsWrapper;
}

TextureManager::~TextureManager()
{
	for (const UPTR<Texture> &item : this->textures)
		this->graphicsWrapper->deleteTexture(item->getId());

	this->textures.clear();
}

Texture *TextureManager::loadDiffuseTexture(const std::string &fileName)
{
	return this->loadTexture(fileName, EMaterialMap::DIFFUSE);
}

Texture *TextureManager::loadNormalTexture(const std::string &fileName)
{
	return this->loadTexture(fileName, EMaterialMap::NORMAL);
}

Texture *TextureManager::loadSpecularTexture(const std::string &fileName)
{
	return this->loadTexture(fileName, EMaterialMap::SPECULAR);
}

Texture *TextureManager::loadAOTexture(const std::string &fileName)
{
	return this->loadTexture(fileName, EMaterialMap::AMBIENT_OCCLUSION);
}

Texture *TextureManager::loadTexture(const std::string &fileName, EMaterialMap::Type mapType)
{
	Texture *result = this->loadExistingTexture(fileName, mapType);

	if (result == nullptr)
	{
		uint32_t width = 0;
		uint32_t height = 0;
		uint8_t bpp = 0;
		MultimediaManager *multimediaManager = MultimediaManager::getInstance();
		void *data = multimediaManager->loadTexture(fileName, &width, &height, &bpp);

		// OpenGL //
		uint32_t unitTexture = mapType - 1;
		uint32_t id = this->graphicsWrapper->setupTexture(width, height, bpp, data, unitTexture);
		delete[] data;

		result = new Texture(id, width, height, mapType, fileName);
		this->textures.emplace_back(result);
	}

	return result;
}

Texture * TextureManager::loadExistingTexture(const std::string &fileName, EMaterialMap::Type mapType)
{
	Texture *result = nullptr;
	for (const UPTR<Texture> &item : this->textures)
	{
		if ((item->getFileName().compare(fileName) == 0) && (item->getMapType() == mapType))
		{
			result = item.get();
			break;
		}
	}

	return result;
}

void TextureManager::deleteTexture(uint32_t id)
{
	this->graphicsWrapper->deleteTexture(id);
}

} // namespace
