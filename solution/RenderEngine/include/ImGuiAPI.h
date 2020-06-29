#ifndef _IMGUI_API_H_
#define _IMGUI_API_H_

#include "AImGuiAPIState.h"
#include "memory_aliases.h"

namespace sre
{

// ImGui + SDL + OpenGL
class ImGuiAPI
{
private:
	UPTR<AImGuiAPIState> state;
	
private:
	ImGuiAPI();
	
	void init(SDL_Window* window, void* glContext);
	void processEvent(SDL_Event* event);
	void onNewFrame(SDL_Window* window);
	void render();
	void changeState(AImGuiAPIState* newState);
	void release();

friend class SDLAPI;
};
	
}

#endif
