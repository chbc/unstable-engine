#include <SDL_image.h>
#include <SDL_opengles.h>
#include <glm/vec3.hpp>

void* loadTexture(const char *fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp)
{
	void *result = nullptr;
	SDL_Surface *surface = IMG_Load(fileName);

	if (surface == nullptr)
	{
		SDL_Log("XXX [SDLAPI] Can't load texture file: %s", fileName);
		return nullptr;
	}

	*outWidth = surface->w;
	*outHeight = surface->h;
	*outBpp = surface->format->BytesPerPixel;

	uint32_t size = surface->pitch * surface->h;
	result = malloc(sizeof(char) * size);
	memcpy(result, surface->pixels, size);

	SDL_FreeSurface(surface);

	return result;
}

uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap)
{
    uint32_t result{ 0 };

    glGenTextures(1, &result);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, result);

    int colorFormat = (bpp == 3) ? GL_RGB : GL_RGBA;

    glTexImage2D
    (
        GL_TEXTURE_2D, 0, colorFormat, width, height, 
        0, colorFormat, GL_UNSIGNED_BYTE, data
    );

    GLint minFilterParam = GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return result;
}
