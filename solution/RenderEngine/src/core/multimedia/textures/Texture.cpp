#include "Texture.h"
#include "FileUtils.h"

namespace sre
{

Texture::Texture(uint32_t id, uint32_t width, uint32_t height, ETextureMap::Type mapType, std::string filePath, uint32_t unitOffset)
	: AAsset(FileUtils::getContentRelativePath(filePath))
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->mapType = mapType;
    this->unit = mapType + unitOffset;
}

uint32_t& Texture::getId()
{
	return this->id;
}

uint32_t Texture::getWidth()
{
	return this->width;
}

uint32_t Texture::getHeight()
{
	return this->height;
}

ETextureMap::Type Texture::getMapType()
{
	return this->mapType;
}

uint32_t Texture::getUnit()
{
    return this->unit;
}

bool Texture::getFlipGreenChannel() const
{
	return this->flipGreenChannel;
}

void Texture::setFlipGreenChannel(bool newValue)
{
	this->flipGreenChannel = newValue;
}

} // namespace
