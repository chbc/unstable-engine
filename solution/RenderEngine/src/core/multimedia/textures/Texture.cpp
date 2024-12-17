#include "Texture.h"

namespace sre
{

Texture::Texture(uint32_t id, uint32_t width, uint32_t height, ETextureMap::Type mapType, std::string fileName, uint32_t unitOffset)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->mapType = mapType;
	this->fileName = fileName;
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

const std::string &Texture::getFileName()
{
	return this->fileName;
}

} // namespace
