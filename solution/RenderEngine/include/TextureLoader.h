#pragma once

#include "Texture.h"

namespace sre
{

class TextureLoader
{
private:
    Texture* load(const std::string &filePath, ETextureMap::Type mapType);
	Texture* loadStandardTexture(const std::string& filePath, ETextureMap::Type mapType);
	Texture* loadHdrTexture(const std::string& filePath, ETextureMap::Type mapType);
    void release(Texture* texture);

friend class AssetsManager;
};

} // namespace
