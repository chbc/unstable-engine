#pragma once

#include "Texture.h"

namespace sre
{

class AGraphicsWrapper;

class TextureLoader
{
protected:
	virtual void getFullFilePath(const std::string& fileName, std::string& result);

private:
    Texture* load(const std::string &fileName, ETextureMap::Type mapType);
    void release(Texture* texture);

friend class AssetsManager;
};

class IconLoader : public TextureLoader
{
protected:
	void getFullFilePath(const std::string& fileName, std::string& result) override;
};

} // namespace
