#include "TextureCreator.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "EngineValues.h"
#include "MultimediaManager.h"

#include <exception>

namespace sre
{

void TextureCreator::init()
{
    this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
    this->shadowIndex = 0;
	this->emptyIndex = 0;
}

void TextureCreator::preRelease()
{
    for (UPTR<Texture>& item : this->createdTextures)
    {
        this->graphicsWrapper->deleteTexture(item->getId());
    }
}

Texture* TextureCreator::createShadowTexture(uint32_t width, uint32_t height)
{
    std::string name{ "_shadow_map_" + std::to_string(this->shadowIndex) };

    uint32_t id = this->graphicsWrapper->createTexture(width, height, ETextureMap::SHADOW + this->shadowIndex);

    Texture *result = new Texture{ id, width, height, ETextureMap::SHADOW, name, this->shadowIndex };
    this->createdTextures.emplace_back(result);
    this->shadowIndex++;

    return result;
}

Texture* TextureCreator::createCubemapTexture(uint32_t width, uint32_t height)
{
    std::string name{ "_cube_map_" + std::to_string(this->shadowIndex) };
    uint32_t id = this->graphicsWrapper->setupDepthCubemap(width, height, ETextureMap::ENVIRONMENT_MAP + this->shadowIndex);

    Texture *result = new Texture{ id, width, height, ETextureMap::ENVIRONMENT_MAP, name, this->shadowIndex };
    this->createdTextures.emplace_back(result);

    this->shadowIndex++;
    return result;
}

Texture* TextureCreator::createEmptyTexture(uint32_t width, uint32_t height)
{
	std::string name{ "_empty_" + std::to_string(this->emptyIndex) };
	uint32_t id = this->graphicsWrapper->createTexture(width, height);

	Texture* result = new Texture{ id, width, height, ETextureMap::GUI, name };
    this->createdTextures.emplace_back(result);

	this->emptyIndex++;
	return result;
}

Texture* TextureCreator::createEmptyFloatingPointTexture(uint32_t width, uint32_t height)
{
	std::string name{ "_empty_" + std::to_string(this->emptyIndex) };
	uint32_t id = this->graphicsWrapper->createFloatingPointTexture(width, height);

	Texture* result = new Texture{ id, width, height, ETextureMap::GUI, name };
    this->createdTextures.emplace_back(result);

	this->emptyIndex++;
	return result;
}

void TextureCreator::saveFramebuffer()
{
    std::string filePath;
    MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();

    if (multimediaManager->saveFileDialog("Save capture", "Image Files (*.png)\0*.png\0", filePath))
    {
        int width = EngineValues::SCREEN_WIDTH;
        int height = EngineValues::SCREEN_HEIGHT;
        unsigned char* pixels = new unsigned char[width * height * 3];

        this->graphicsWrapper->readFramebuffer(width, height, pixels);
        multimediaManager->saveTexture(pixels, filePath.c_str(), width, height);

        delete[] pixels;
    }
}

} // namespace
