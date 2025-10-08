#pragma once

#include "Texture.h"

namespace sre
{

class HDRTextureLoader
{
private:
    Texture* load(const std::string& filePath, size_t mapType);

friend class AssetsManager;
};

} // namespace
