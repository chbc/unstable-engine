#include "SDLAPI.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "InputHandler.h"
#include "EngineValues.h"
#include "GUIButtonComponent.h"
#include "Entity.h"

namespace sre
{

void SDLAPI::init()
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
		EngineValues::APPLICATION_NAME.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT,
		flags
	);

	if (this->window == NULL)
		throw this->getError();

	void *context = SDL_GL_CreateContext(this->window);

	if (context == NULL)
		throw this->getError();

	this->imGuiAPI = UPTR<ImGuiAPI>{ new ImGuiAPI };
	this->imGuiAPI->init(this->window, context);
}

void SDLAPI::swapBuffers()
{
	this->imGuiAPI->onNewFrame(this->window);
	this->imGuiAPI->render();
	SDL_GL_SwapWindow(this->window);
}

void SDLAPI::processInput(InputHandler *inputHandler, const std::vector<GUIButtonComponent*>& guiButtons)
{
	glm::vec2 position;

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		this->imGuiAPI->processEvent(&currentEvent);
		
		switch (currentEvent.type)
		{
			case SDL_QUIT:		inputHandler->onQuit(); break;
			case SDL_KEYDOWN:	inputHandler->onKeyEvent(currentEvent.key.keysym.sym, true); break;
			case SDL_KEYUP:		inputHandler->onKeyEvent(currentEvent.key.keysym.sym, false); break;

			case SDL_MOUSEMOTION:
				position = glm::vec2{currentEvent.motion.x, currentEvent.motion.y};
				inputHandler->onMouseMove(position);

				position = glm::vec2{currentEvent.motion.xrel, currentEvent.motion.yrel};
				inputHandler->onMouseMoveRelative(position);
				break;

			case SDL_MOUSEBUTTONDOWN:
				position = glm::vec2{currentEvent.button.x, currentEvent.button.y};

				if (!guiButtons.empty() && !this->checkButtonPress(inputHandler, guiButtons, position))
					inputHandler->onMouseButtonEvent(currentEvent.button.button, position, true);
				break;

			case SDL_MOUSEBUTTONUP:
				position = glm::vec2{currentEvent.button.x, currentEvent.button.y};
				inputHandler->onMouseButtonEvent(currentEvent.button.button, position, false);
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
	std::string resultFileName = ASSETS_FOLDER + fileName;
	SDL_Surface *surface = IMG_Load(resultFileName.c_str());

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

void SDLAPI::log(const std::string& type, const std::string& message)
{
	SDL_Log("[%s]: %s", type.c_str(), message.c_str());
}

void SDLAPI::release()
{
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}


bool SDLAPI::checkButtonPress(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition)
{
	pressPosition.x /= EngineValues::SCREEN_WIDTH;
	pressPosition.y /= EngineValues::SCREEN_HEIGHT;

	for (GUIButtonComponent* item : guiButtons)
	{
		if (item->isInside(pressPosition))
		{
			inputHandler->onGUIButtonPressed(item, item->getEntity()->getName());
			return true;
		}
	}

	return false;
}

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

} // namespace
