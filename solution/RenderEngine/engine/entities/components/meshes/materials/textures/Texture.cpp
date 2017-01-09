#include "Texture.h"

namespace sre
{

Texture::Texture(uint32_t id, uint32_t width, uint32_t height)
{
	this->id = id;
	this->width = width;
	this->height = height;
}

uint32_t Texture::getId()
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

} // namespace
