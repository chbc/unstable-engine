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
	SPTR<AImGuiAPIState> state;
	
	SPTR<AImGuiAPIState> emptyState;
	SPTR<AImGuiAPIState> concreteState;

private:
	ImGuiAPI();
	
	void init(SDL_Window* window, void* glContext);
	void processEvent(SDL_Event* event);
	void onNewFrame(SDL_Window* window);
	void render();
	void setEditorMode(bool value);
	void release();

friend class SDLAPI;
friend class SDLAndroidAPI;
};
	
}

#endif
