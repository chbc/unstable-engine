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
	return this->loadTexture(fileName, 0);
}

Texture *TextureManager::loadNormalTexture(const std::string &fileName)
{
	return this->loadTexture(fileName, 1);
}

Texture *TextureManager::loadTexture(const std::string &fileName, uint32_t unit)
{
	Texture *result = nullptr;

	uint32_t width = 0;
	uint32_t height = 0;
	uint8_t bpp = 0;
	MultimediaManager *multimediaManager = MultimediaManager::getInstance();
	void *data = multimediaManager->loadTexture(fileName, &width, &height, &bpp);

	// OpenGL //
	uint32_t id = this->graphicsWrapper->setupTexture(width, height, bpp, data, unit);
	delete[] data;

	result = new Texture(id, width, height);
	this->textures.emplace_back(result);

	return result;
}

void TextureManager::deleteTexture(uint32_t id)
{
	this->graphicsWrapper->deleteTexture(id);
}

} // namespace
