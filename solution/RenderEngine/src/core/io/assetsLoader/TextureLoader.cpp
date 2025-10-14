#include "TextureLoader.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "FileUtils.h"

namespace sre
{

Texture* TextureLoader::load(const std::string& filePath, ETextureMap::Type mapType)
{
	EAssetType assetType = FileUtils::getAssetType(filePath);
	Texture* result = nullptr;
    switch(assetType)
    {
        case EAssetType::TEXTURE:
			result = this->loadStandardTexture(filePath, mapType);
            break;
        case EAssetType::HDR_TEXTURE:
			result = this->loadHdrTexture(filePath, mapType);
            break;
        default:
            throw "[TextureLoader] - Unsupported texture type: " + filePath;
	}

    return result;
}

Texture* TextureLoader::loadStandardTexture(const std::string& filePath, ETextureMap::Type mapType)
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

Texture* TextureLoader::loadHdrTexture(const std::string& filePath, ETextureMap::Type mapType)
{
    MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();

    int width{ 0 }, height{ 0 }, bpp{ 0 };
    float* data = multimediaManager->loadHdrTexture(filePath, &width, &height, &bpp);

    // OpenGL //
    uint32_t id{ 0 };

    if (mapType == ETextureMap::IBL_BRDF_LUT)
    {
        id = graphicsWrapper->setupHdrTexture(width, height, bpp, data, mapType, false);
    }
    else
    {
        uint32_t faceSize{ 32 };
        bool mipmap{ false };
        if (mapType == ETextureMap::ENVIRONMENT_MAP)
        {
            faceSize = 512;
        }
        else if (mapType == ETextureMap::IBL_PREFILTER)
        {
            faceSize = 128;
            mipmap = true;
        }

        id = graphicsWrapper->setupHdrCubemap(width, height, bpp, data, mapType, faceSize, mipmap);
    }
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
