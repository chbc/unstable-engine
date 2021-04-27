#ifdef __ANDROID__

#include "SDLAndroidAPI.h"

#include <SDL_image.h>
#include <SDL_test_common.h>
#include "SDL_opengles2.h"
#include <string>

#include "InputHandler.h"
#include "EngineValues.h"
#include "GUIButtonComponent.h"
#include "Entity.h"

namespace sre
{

static SDLTest_CommonState* state;
static SDL_GLContext* context = NULL;

void SDLAndroidAPI::init()
{
	SDL_Log("XXX SDL init");

	const int depth = 16;
	char** argv = new char* [1];
	argv[0] = new char[15];
	memcpy(argv[0], EngineValues::APPLICATION_NAME.c_str(), 128);

	/* Initialize test framework */
	state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);

	/* Set OpenGL parameters */
	state->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
	state->gl_red_size = 5;
	state->gl_green_size = 5;
	state->gl_blue_size = 5;
	state->gl_depth_size = depth;
	state->gl_major_version = 2;
	state->gl_minor_version = 0;
	state->gl_profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

	SDLTest_CommonInit(state);

	context = (SDL_GLContext*)SDL_calloc(state->num_windows, sizeof(context));

	/* Create OpenGL ES contexts */
	context[0] = SDL_GL_CreateContext(state->windows[0]);

	if (state->render_flags & SDL_RENDERER_PRESENTVSYNC)
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	SDL_Log("XXX Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
	SDL_Log("\n");
	SDL_Log("XXX Vendor     : %s\n", glGetString(GL_VENDOR));
	SDL_Log("XXX Renderer   : %s\n", glGetString(GL_RENDERER));
	SDL_Log("XXX Version    : %s\n", glGetString(GL_VERSION));
	SDL_Log("XXX Extensions : %s\n", glGetString(GL_EXTENSIONS));
	SDL_Log("\n");

	/* Set rendering settings for each context */
	SDL_GL_MakeCurrent(state->windows[0], context[0]);

	SDL_GL_GetDrawableSize(state->windows[0], &EngineValues::SCREEN_WIDTH, &EngineValues::SCREEN_HEIGHT);

	this->window = state->windows[0];

	delete[] argv[0];
	delete[] argv;
}

void SDLAndroidAPI::onBeginFrame() { }

void SDLAndroidAPI::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

void SDLAndroidAPI::setEditorMode(bool value) { }

void SDLAndroidAPI::processInput(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons)
{
	glm::vec2 position;

	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		switch (currentEvent.type)
		{
			case SDL_QUIT: inputHandler->onQuit(); break;

			case SDL_MOUSEMOTION:
				position = glm::vec2{ currentEvent.motion.x, currentEvent.motion.y };
				inputHandler->onMouseMove(position);

				position = glm::vec2{ currentEvent.motion.xrel, currentEvent.motion.yrel };
				inputHandler->onMouseMoveRelative(position);
				break;

			case SDL_MOUSEBUTTONDOWN:
				position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };

				SDL_Log("XXX MOUSE DOWN (%.2f, %.2f)", position.x, position.y);

				if (!guiButtons.empty() && !this->checkButtonPress(inputHandler, guiButtons, position))
					inputHandler->onMouseButtonEvent(currentEvent.button.button, position, true);
				break;

			case SDL_MOUSEBUTTONUP:
				position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };
				inputHandler->onMouseButtonEvent(currentEvent.button.button, position, false);
				break;
		}
	}
}

bool SDLAndroidAPI::checkClosePressed()
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

unsigned int SDLAndroidAPI::getTicks()
{
	return SDL_GetTicks();
}

void SDLAndroidAPI::delay(unsigned int timeMS)
{
	SDL_Delay(timeMS);
}

void* SDLAndroidAPI::loadTexture(const std::string& fileName, uint32_t* outWidth, uint32_t* outHeight, uint8_t* outBpp)
{
	void* result = nullptr;

	std::string resultFileName = ASSETS_FOLDER + fileName;
	SDL_RWops* file = SDL_RWFromFile(resultFileName.c_str(), "rb");
	SDL_Surface* surface = IMG_Load_RW(file, 1);

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

void SDLAndroidAPI::log(const std::string& type, const std::string& message)
{
	SDL_Log("[%s]: %s", type.c_str(), message.c_str());
}

void SDLAndroidAPI::release()
{
	int i;

	if (context != NULL) {
		for (i = 0; i < state->num_windows; i++) {
			if (context[i]) {
				SDL_GL_DeleteContext(context[i]);
			}
		}

		SDL_free(context);
	}

	IMG_Quit();
	SDLTest_CommonQuit(state);
}

bool SDLAndroidAPI::checkButtonPress(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition)
{
	pressPosition.x /= EngineValues::SCREEN_WIDTH;
	pressPosition.y /= EngineValues::SCREEN_HEIGHT;

	for (GUIButtonComponent* item : guiButtons)
	{
		if (item->getEntity()->isEnabled() && item->isInside(pressPosition))
		{
			inputHandler->onGUIButtonPressed(item, item->getEntity()->getName());
			return true;
		}
	}

	return false;
}

} // namespace

#endif
