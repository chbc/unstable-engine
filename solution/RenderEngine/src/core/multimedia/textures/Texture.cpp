#include "Texture.h"

namespace sre
{

Texture::Texture(uint32_t id, uint32_t width, uint32_t height, ETextureMap::Type mapType, std::string filePath, uint32_t unitOffset)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->mapType = mapType;
	this->filePath = filePath;
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

const std::string &Texture::getFilePath()
{
	return this->filePath;
}

} // namespace
