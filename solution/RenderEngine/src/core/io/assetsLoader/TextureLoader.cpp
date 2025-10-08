#include "TextureLoader.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

Texture* TextureLoader::load(const std::string& filePath, size_t mapType)
{
    MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();

    uint32_t width, height;
    uint8_t bpp = 0;
    void* data = multimediaManager->loadTexture(filePath, &width, &height, &bpp);

    // OpenGL //
    bool genMipmap = (mapType != ETextureMap::GUI);
    uint32_t id = graphicsWrapper->setupTexture(width, height, bpp, data, mapType, genMipmap);
    free(data);

    Texture* result = new Texture(id, width, height, mapType, filePath);
    return result;
}

void TextureLoader::release(Texture* texture)
{
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
    graphicsWrapper->deleteTexture(texture->getId());
}

} // namespace
