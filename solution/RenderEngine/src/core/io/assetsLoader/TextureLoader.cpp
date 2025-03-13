#include "TextureLoader.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "Paths.h"

#include <exception>

namespace sre
{
void TextureLoader::getFullFilePath(const std::string& fileName, std::string& result)
{
    Paths().buildMediaFilePath(fileName.c_str(), result);
}

Texture* TextureLoader::load(const std::string& fileName, ETextureMap::Type mapType)
{
    std::string filePath;
    MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	
    this->getFullFilePath(fileName, filePath);

    uint32_t width, height;
    uint8_t bpp = 0;
    void* data = multimediaManager->loadTexture(filePath, &width, &height, &bpp);

    // OpenGL //
    bool genMipmap = (mapType != ETextureMap::GUI);
    uint32_t id = graphicsWrapper->setupTexture(width, height, bpp, data, mapType, genMipmap);
    free(data);

    Texture* result = new Texture(id, width, height, mapType, fileName);
    return result;
}

void TextureLoader::release(Texture* texture)
{
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
    graphicsWrapper->deleteTexture(texture->getId());
}

void IconLoader::getFullFilePath(const std::string& fileName, std::string& result)
{
    result = fileName;
}

} // namespace
