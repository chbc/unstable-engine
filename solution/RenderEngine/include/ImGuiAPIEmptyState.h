#pragma once

#include "AImGuiAPIState.h"

namespace sre
{

class ImGuiAPIEmptyState : public AImGuiAPIState
{
private:
	void init(SDL_Window* window, void* glContext) {}
	void processEvent(SDL_Event* event) {}
	void onNewFrame() {}
	void render() {}
	void release() {}
};
	
} // namespace
