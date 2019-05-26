#include "SDLAPI.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <engine/core/io/InputHandler.h>
#include <cstring>

namespace sre
{

void SDLAPI::init(float width, float height, const std::string &title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw this->getError();

    int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw IMG_GetError();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	this->window = SDL_CreateWindow
	(
		title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(width), static_cast<int>(height),
		flags
	);

	if (this->window == NULL)
		throw this->getError();

	void *context = SDL_GL_CreateContext(this->window);

	if (context == NULL)
		throw this->getError();
}

void SDLAPI::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

void SDLAPI::processInput(InputHandler *inputHandler)
{
	glm::vec2 position;

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		switch (currentEvent.type)
		{
			case SDL_QUIT:		inputHandler->onQuit(); break;
			case SDL_KEYDOWN:	inputHandler->onKeyPressed(currentEvent.key.keysym.sym); break;
			case SDL_KEYUP:		inputHandler->onKeyReleased(currentEvent.key.keysym.sym); break;

			case SDL_MOUSEMOTION:
				position = glm::vec2{currentEvent.motion.x, currentEvent.motion.y};
				inputHandler->onMouseMove(position);

				position = glm::vec2{currentEvent.motion.xrel, currentEvent.motion.yrel};
				inputHandler->onMouseMoveRelative(position);
				break;

			case SDL_MOUSEBUTTONDOWN:
				position = glm::vec2{currentEvent.button.x, currentEvent.button.y};
				inputHandler->onMouseButtonPressed(currentEvent.button.button, position);
				break;

			case SDL_MOUSEBUTTONUP:
				position = glm::vec2{currentEvent.button.x, currentEvent.button.y};
				inputHandler->onMouseButtonReleased(currentEvent.button.button, position);
				break;

			case SDL_MOUSEWHEEL:
				inputHandler->onMouseWheel(currentEvent.wheel.y);
				break;
		}
	}
}

bool SDLAPI::checkClosePressed()
{
	bool result = false;
	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		if (currentEvent.type == SDL_QUIT)
		{
			result = true;
			break;
		}
	}

	return result;
}

unsigned int SDLAPI::getTicks()
{
	return SDL_GetTicks();
}

void SDLAPI::delay(unsigned int timeMS)
{
	SDL_Delay(timeMS);
}

void *SDLAPI::loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp)
{
	void *result = nullptr;
	SDL_Surface *surface = IMG_Load(fileName.c_str());

	if (surface == nullptr)
		throw "[SDLAPI] Can't load texture file: " + fileName;

	*outWidth = surface->w;
	*outHeight = surface->h;
	*outBpp = surface->format->BytesPerPixel;

	uint32_t size = surface->pitch * surface->h;
	result = malloc(sizeof(char) * size);
	memcpy(result, surface->pixels, size);

	SDL_FreeSurface(surface);

	return result;
}

void SDLAPI::release()
{
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

} // namespace
