#include "SDLAPI.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "EngineValues.h"
#include "GUIButtonComponent.h"
#include "Entity.h"
#include "Input.h"

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

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
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

void SDLAPI::onFrameBegin()
{
	this->imGuiAPI->onNewFrame(this->window);
}

void SDLAPI::swapBuffers()
{
	this->imGuiAPI->render();
	SDL_GL_SwapWindow(this->window);
}

void SDLAPI::setExecutionMode(EExecutionMode::Type mode)
{
	this->imGuiAPI->setExecutionMode(mode);
}

void SDLAPI::processInput(const std::vector<GUIButtonComponent*>& guiButtons)
{
	SDL_Event currentEvent;

	Input::clear();
	while (SDL_PollEvent(&currentEvent))
	{
		this->imGuiAPI->processEvent(&currentEvent);
		this->processInput(guiButtons, currentEvent);
	}
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

void SDLAPI::processInput(const std::vector<GUIButtonComponent*>& guiButtons, SDL_Event& currentEvent)
{
	glm::vec2 position;

	switch (currentEvent.type)
	{
		case SDL_QUIT:		Input::CloseButton = true; break;
		case SDL_KEYDOWN:	Input::addKey(static_cast<Key>(currentEvent.key.keysym.sym)); break;
		case SDL_KEYUP:		Input::removeKeyDown(static_cast<Key>(currentEvent.key.keysym.sym)); break;

		case SDL_MOUSEMOTION:
			Input::setMousePosition(currentEvent.motion.x, currentEvent.motion.y);
			Input::setMouseDeltaPosition(currentEvent.motion.xrel, currentEvent.motion.yrel);
			break;

		case SDL_MOUSEBUTTONDOWN:
			position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };
			if (guiButtons.empty() || !this->checkButtonPress(guiButtons, position))
				Input::addMouseButton(static_cast<MouseButton>(currentEvent.button.button));
			break;

		case SDL_MOUSEBUTTONUP:
			Input::removeMouseButtonDown(static_cast<MouseButton>(currentEvent.button.button));
			break;

		case SDL_MOUSEWHEEL:
			Input::setMouseWheel(currentEvent.wheel.y);
			break;

		case SDL_WINDOWEVENT:
			const SDL_WindowEvent& window = currentEvent.window;
			if (window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				EngineValues::SCREEN_WIDTH = window.data1;
				EngineValues::SCREEN_HEIGHT = window.data2;
				EngineValues::updateAspectRatio();
			}
			break;
	}
}

bool SDLAPI::checkButtonPress(const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition)
{
	pressPosition.x /= EngineValues::SCREEN_WIDTH;
	pressPosition.y /= EngineValues::SCREEN_HEIGHT;

	bool done = false;

	for (GUIButtonComponent* item : guiButtons)
	{
		bool pressed = false;
		if (!done && item->getEntity()->isEnabled() && item->isInside(pressPosition))
		{
			pressed = true;
			done = true;
		}

		item->setPressed(pressed);
	}

	return false;
}

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

void SDLAPI::showMessageBox(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), nullptr);
}

void SDLAPI::showErrorMessageBox(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), nullptr);
}

} // namespace
