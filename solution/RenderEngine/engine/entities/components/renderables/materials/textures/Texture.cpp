#include "Texture.h"

Texture::Texture(unsigned int id, unsigned int width, unsigned int height, Type type)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->type = type;
}
