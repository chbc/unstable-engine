#include "HDRTextureLoader.h"

#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

Texture* HDRTextureLoader::load(const std::string& filePath, ETextureMap::Type mapType)
{
    MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
    AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();

    int width{ 0 }, height{ 0 }, bpp{ 0 };
    float* data = multimediaManager->loadHdrTexture(filePath, &width, &height, &bpp);

    // OpenGL //
    uint32_t id{ 0 };

    if (mapType == ETextureMap::IBL_BRDF_LUT)
    {
        id = graphicsWrapper->setupFloatingPointTexture(width, height, bpp, data, mapType, false);
    }
    else
    {
        uint32_t faceSize{ 32 };
        bool mipmap{ false };

        if (mapType == ETextureMap::IBL_PREFILTER)
        {
            faceSize = 128;
            mipmap = true;
        }

        id = graphicsWrapper->setupHdrFromCrossedImage(width, height, data, faceSize, mipmap);
    }
    free(data);

    Texture* result = new Texture(id, width, height, mapType, filePath);
    return result;
}

} // namespace
