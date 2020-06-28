#ifndef _IMGUI_API_STATE_H_
#define _IMGUI_API_STATE_H_

#include "AImGuiAPIState.h"

namespace sre
{

	class ImGuiAPIState : public AImGuiAPIState
	{
	private:
		void init(SDL_Window* window, void* glContext);
		void processEvent(SDL_Event* event);
		void onNewFrame(SDL_Window* window);
		void render();
		void release();
	};

} // namespace

#endif
