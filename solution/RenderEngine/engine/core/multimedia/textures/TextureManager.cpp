#include "TextureManager.h"
#include <exception>
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

void TextureManager::init()
{
    this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
    this->shadowIndex = 0;
}

void TextureManager::release()
{
    for (const UPTR<Texture> &item : this->textures)
        this->deleteTexture(item->getId());

    this->textures.clear();
}

Texture *TextureManager::loadGUITexture(const std::string &fileName)
{
    return this->loadTexture(fileName, EMaterialMap::GUI);
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

Texture *TextureManager::loadShadowTexture(uint32_t width, uint32_t height)
{
    std::string name{ "_shadow_map_" + std::to_string(this->shadowIndex) };

    uint32_t id = this->graphicsWrapper->setupTexture(width, height, EMaterialMap::SHADOW + this->shadowIndex);

    Texture *result = new Texture{ id, width, height, EMaterialMap::SHADOW, name, this->shadowIndex };
    this->textures.emplace_back(result);

    this->shadowIndex++;
    return result;
}

Texture *TextureManager::loadCubemapTexture(uint32_t width, uint32_t height)
{
    std::string name{ "_cube_map_" + std::to_string(this->shadowIndex) };
    uint32_t id = this->graphicsWrapper->generateCubemap(width, height, EMaterialMap::SHADOW + this->shadowIndex);

    Texture *result = new Texture{ id, width, height, EMaterialMap::SHADOW, name, this->shadowIndex };
    this->textures.emplace_back(result);

    this->shadowIndex++;
    return result;
}

Texture *TextureManager::loadTexture(const std::string &fileName, EMaterialMap::Type mapType)
{
    Texture *result = this->loadExistingTexture(fileName, mapType);

    if (result == nullptr)
    {
        uint32_t width = 0;
        uint32_t height = 0;
        uint8_t bpp = 0;
        MultimediaManager *multimediaManager = SingletonsManager::getInstance()->resolve<MultimediaManager>();
        void *data = multimediaManager->loadTexture(fileName, &width, &height, &bpp);

        // OpenGL //
        bool genMipmap = (mapType != EMaterialMap::GUI);
        uint32_t id = this->graphicsWrapper->setupTexture(width, height, bpp, data, mapType, genMipmap);
        free(data);

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
