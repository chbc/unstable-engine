#include "SDLAPI.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_test_common.h>
#include "InputHandler.h"
#include <cstring>

namespace sre
{

static SDLTest_CommonState* state;
static SDL_GLContext* context = NULL;
static int depth = 16;

static void quit(int rc)
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

	SDLTest_CommonQuit(state);
	exit(rc);
}

void SDLAPI::init(float width, float height, const std::string &title)
{
	SDL_Event event;
	Uint32 then, now, frames;
	int status;

	/* Enable standard application logging */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	SDL_Log("XXX SDL init 1");


	/* Initialize test framework */
	char** arguments = (char**)malloc(10 * sizeof(char*));
	arguments[0] = "T";
	
	state = SDLTest_CommonCreateState(arguments, SDL_INIT_VIDEO);
	if (!state)
		return;

	SDL_Log("XXX SDL init 2");

	/* Set OpenGL parameters */
	state->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
	state->gl_red_size = 5;
	state->gl_green_size = 5;
	state->gl_blue_size = 5;
	state->gl_depth_size = depth;
	state->gl_major_version = 1;
	state->gl_minor_version = 1;
	state->gl_profile_mask = SDL_GL_CONTEXT_PROFILE_ES;

	if (!SDLTest_CommonInit(state)) {
		quit(2);
	}

	delete[] arguments;

	SDL_Log("XXX SDL init 3");

	context = (SDL_GLContext*)SDL_calloc(state->num_windows, sizeof(context));
	if (context == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "XXX Out of memory!\n");
		quit(2);
	}

	SDL_Log("XXX SDL init 4");

	context[0] = SDL_GL_CreateContext(state->windows[0]);
	if (!context[0]) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "XXX SDL_GL_CreateContext(): %s\n", SDL_GetError());
		quit(2);
	}

	SDL_Log("XXX SDL init 5");

	if (state->render_flags & SDL_RENDERER_PRESENTVSYNC) {
		SDL_GL_SetSwapInterval(1);
	}
	else {
		SDL_GL_SetSwapInterval(0);
	}

	SDL_Log("XXX SDL init 6");

	status = SDL_GL_MakeCurrent(state->windows[0], context[0]);
	if (status)
	{
		SDL_Log("XXX SDL_GL_MakeCurrent(): %s\n", SDL_GetError());
	}

	SDL_Log("XXX SDL init 7");

	this->window = state->windows[0];
	/*
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Log("XXX SDL init ERROR 8: #s", IMG_GetError());
		quit(1);
	}
	*/
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

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

} // namespace
