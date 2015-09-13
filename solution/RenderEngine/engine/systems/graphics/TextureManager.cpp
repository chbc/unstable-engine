#include "TextureManager.h"
#include <exception>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

namespace graphics
{

IMPLEMENT_SINGLETON(TextureManager);

TextureManager::TextureManager()
{
}

bool TextureManager::init()
{
	return true;
}

void TextureManager::release()
{
}

Texture *TextureManager::loadTexture(const std::string &fileName)
{
    /*
	SDL_Surface *img1 = IMG_Load(fileName);

	if (img1 == NULL)
		throw std::exception();

	unsigned int colorFormat;

	colorFormat = GL_RGBA;

	if (img1->flags & SDL_SRCALPHA)
		colorFormat = GL_RGBA;
	else
		colorFormat = GL_RGB;

	// OpenGL //
	unsigned int id = 0;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, img1->w, img1->h, 0, colorFormat, GL_UNSIGNED_BYTE, img1->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	Texture *newTexture = new Texture(id, img1->w, img1->h);

	SDL_FreeSurface(img1);

	return newTexture;
*/
	return NULL;
}

void TextureManager::deleteTexture(unsigned int id)
{
    glDeleteTextures(1, &id);
}

} // namespace graphics
