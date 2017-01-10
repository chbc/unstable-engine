#include "SDLAPI.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <engine/systems/input/InputHandler.h>

namespace sre
{

void SDLAPI::init(int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw this->getError();

    int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw IMG_GetError();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	this->window = SDL_CreateWindow("SudaRA Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if (this->window == NULL)
		throw this->getError();

	this->context = SDL_GL_CreateContext(this->window);

	if (this->context == NULL)
		throw this->getError();

	this->event = new SDL_Event;
}

void SDLAPI::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

void SDLAPI::processInput(InputHandler *inputHandler)
{
	glm::vec2 position;
	while (SDL_PollEvent(this->event) != 0)
	{
		switch (this->event->type)
		{
			case SDL_QUIT:		inputHandler->onQuit(); break;
			case SDL_KEYDOWN:	inputHandler->onKeyPressed(this->event->key.keysym.sym); break;
			case SDL_KEYUP:		inputHandler->onKeyReleased(this->event->key.keysym.sym); break;

			case SDL_MOUSEMOTION:
				position = glm::vec2
				{
					static_cast<float>(this->event->motion.xrel), 
					static_cast<float>(this->event->motion.yrel) 
				};
				inputHandler->onMouseMove(position);
				break;

			case SDL_MOUSEBUTTONDOWN:
				position = glm::vec2
				{ 
					static_cast<float>(this->event->button.x), 
					static_cast<float>(this->event->button.y) 
				};
				inputHandler->onMouseButtonPressed(this->event->button.button, position);
				break;

			case SDL_MOUSEBUTTONUP:
				position = glm::vec2
				{ 
					static_cast<float>(this->event->button.x), 
					static_cast<float>(this->event->button.y) 
				};
				inputHandler->onMouseButtonReleased(this->event->button.button, position);
				break;
		}
	}
}

bool SDLAPI::checkClosePressed()
{
	bool result = false;
	while (SDL_PollEvent(this->event) != 0)
	{
		if (this->event->type == SDL_QUIT)
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
	result = new char[size];
	memcpy_s(result, size, surface->pixels, size);

	SDL_FreeSurface(surface);

	return result;
}

void SDLAPI::release()
{
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();

	delete this->event;
}

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

} // namespace
