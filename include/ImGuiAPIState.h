#ifndef _IMGUI_API_STATE_H_
#define _IMGUI_API_STATE_H_

#include "AImGuiAPIState.h"

namespace sre
{

class ImGuiAPIState : public AImGuiAPIState
{
protected:
	void init(SDL_Window* window, void* glContext) override;
	void processEvent(SDL_Event* event) override;
	void onNewFrame(SDL_Window* window) override;
	void render() override;
	void release() override;
};

} // namespace

#endif
