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

Texture *TextureManager::loadTexture(const std::string &fileName)
{
	Texture *result = nullptr;

	uint32_t width = 0;
	uint32_t height = 0;
	void *data = nullptr;
	MultimediaManager *multimediaManager = MultimediaManager::getInstance();
	multimediaManager->loadTexture(fileName, &width, &height, data);


	// OpenGL //
	uint32_t id = this->graphicsWrapper->setupTexture(width, height, data);
	delete data;

	result = new Texture(id, width, height);
	this->textures.emplace_back(result);

	return result;
}

void TextureManager::deleteTexture(uint32_t id)
{
	this->graphicsWrapper->deleteTexture(id);
}

} // namespace
