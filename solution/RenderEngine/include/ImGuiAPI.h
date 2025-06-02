#pragma once

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
	void onNewFrame();
	void render();
	void setExecutionMode(EExecutionMode::Type mode);
	void release();

friend class SDLAPI;
friend class SDLAndroidAPI;
};
	
}
