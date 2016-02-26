#include "MultimediaManager.h"
#include <iostream>

namespace sre
{

IMPLEMENT_SINGLETON(MultimediaManager);

MultimediaManager::MultimediaManager()
{
    this->window = NULL;
}

bool MultimediaManager::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		this->displayError();
		return false;
	}

    //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	this->window = SDL_CreateWindow("SudaRA Render Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags);

	if (this->window == NULL)
	{
		this->displayError();
		return false;
	}

	this->context = SDL_GL_CreateContext(this->window);
	if (this->context == NULL)
    {
        this->displayError();
        return false;
    }

	return true;
}

void MultimediaManager::release()
{
    SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void MultimediaManager::displayError()
{
	std::cout << "Error: " << SDL_GetError() << std::endl;
}

void MultimediaManager::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

} // namespace
