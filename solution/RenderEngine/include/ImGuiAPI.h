#ifndef _IMGUI_API_H_
#define _IMGUI_API_H_

#include "AImGuiAPIState.h"
#include "memory_aliases.h"
#include "EExecutionMode.h"

namespace sre
{

// ImGui + SDL + OpenGL
class ImGuiAPI
{
private:
	SPTR<AImGuiAPIState> state;
	
	SPTR<AImGuiAPIState> emptyState;
	SPTR<AImGuiAPIState> concreteState;

private:
	ImGuiAPI();
	
	void init(SDL_Window* window, void* glContext);
	void processEvent(SDL_Event* event);
	void onNewFrame(SDL_Window* window);
	void render();
	void setExecutionMode(EExecutionMode::Type mode);
	void release();

friend class SDLAPI;
friend class SDLAndroidAPI;
};
	
}

#endif
