#ifndef _MULTIMEDIA_MANAGER_H_
#define _MULTIMEDIA_MANAGER_H_

#include <engine/util/singleton_macros.h>
#include <SDL/SDL.h>

namespace sre
{

/*!
	Class for window management
*/
class MultimediaManager
{
	DECLARE_SINGLETON(MultimediaManager);

	private:
		SDL_Window *window;
		SDL_GLContext context;

		void displayError();

	public:
		static const int WIDTH	= 800;
		static const int HEIGHT	= 600;

		void swapBuffers();
};

} // namespace

#endif
