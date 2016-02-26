#include "InputHandler.h"

namespace sre
{

InputHandler::InputHandler()
{
}

void InputHandler::process()
{
	while (SDL_PollEvent(&this->event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:		this->onQuit(); break;
	        case SDL_KEYDOWN:	this->onKeyPressed(event.key.keysym.sym); break;
	        case SDL_KEYUP:		this->onKeyReleased(event.key.keysym.sym); break;

			case SDL_MOUSEMOTION:
				this->onMouseMove(Vector(event.motion.xrel, event.motion.yrel)); 
				break;

			case SDL_MOUSEBUTTONDOWN:
				this->onMouseButtonPressed(event.button.button, Vector(event.button.x, event.button.y));
				break;

			case SDL_MOUSEBUTTONUP:
				this->onMouseButtonReleased(event.button.button, Vector(event.button.x, event.button.y));
				break;
		}
	}
}

} // namespace
