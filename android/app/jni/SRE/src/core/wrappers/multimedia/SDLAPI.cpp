#include "SDLAPI.h"
#include <SDL_image.h>
#include <SDL_test_common.h>
#include "InputHandler.h"
#include <cstring>

// XXX #define HAVE_OPENGLES2

#include "SDL_opengles2.h"

namespace sre
{

static SDLTest_CommonState* state;
static SDL_GLContext* context = NULL;

void SDLAPI::init(float width, float height, const std::string &title)
{
	const int depth = 16;
	char** argv = new char*[1];
	argv[0] = new char[15]{"Nome do jogo"};

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
	SDL_Log("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
	SDL_Log("\n");
	SDL_Log("Vendor     : %s\n", glGetString(GL_VENDOR));
	SDL_Log("Renderer   : %s\n", glGetString(GL_RENDERER));
	SDL_Log("Version    : %s\n", glGetString(GL_VERSION));
	SDL_Log("Extensions : %s\n", glGetString(GL_EXTENSIONS));
	SDL_Log("\n");

	/* Set rendering settings for each context */
	int w, h;
	SDL_GL_MakeCurrent(state->windows[0], context[0]);

	SDL_GL_GetDrawableSize(state->windows[0], &w, &h);
	glViewport(0, 0, w, h);

	delete [] argv[0];
	delete [] argv;
}

void SDLAPI::swapBuffers()
{
	SDL_GL_SwapWindow(state->windows[0]);
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

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

} // namespace
