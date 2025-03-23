#pragma once

#include "Texture.h"

namespace sre
{

class AGraphicsWrapper;

class TextureLoader
{
private:
    Texture* load(const std::string &filePath, ETextureMap::Type mapType);
    void release(Texture* texture);

friend class AssetsManager;
};

} // namespace
