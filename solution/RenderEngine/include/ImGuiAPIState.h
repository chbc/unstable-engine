#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "AImGuiAPIState.h"

namespace sre
{

class ImGuiAPIState : public AImGuiAPIState
{
protected:
	void init(SDL_Window* window, void* glContext) override;
	void processEvent(SDL_Event* event) override;
	void onNewFrame() override;
	void render() override;
	void release() override;
};

} // namespace

#endif
