#pragma once

#include "Texture.h"

namespace sre
{

class HDRTextureLoader
{
private:
    Texture* load(const std::string& filePath, ETextureMap::Type mapType);

friend class AssetsManager;
};

} // namespace
