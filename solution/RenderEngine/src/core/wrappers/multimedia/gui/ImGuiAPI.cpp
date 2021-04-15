#include "ImGuiAPI.h"

#if defined(DEBUG) && !defined(__ANDROID__)
#include "ImGuiAPIState.h"
#else
#include "ImGuiAPIEmptyState.h"
#endif

namespace sre
{

ImGuiAPI::ImGuiAPI()
{
#if defined(DEBUG) && !defined(__ANDROID__)
	this->state = make_unique<ImGuiAPIState>();
#else
	this->state = make_unique<ImGuiAPIEmptyState>();
#endif
}
	
void ImGuiAPI::init(SDL_Window* window, void* glContext)
{
	this->state->init(window, glContext);
}

void ImGuiAPI::processEvent(SDL_Event* event)
{
	this->state->processEvent(event);
}

void ImGuiAPI::onNewFrame(SDL_Window* window)
{
	this->state->onNewFrame(window);
}

void ImGuiAPI::render()
{
	this->state->render();
}

void ImGuiAPI::release()
{
	this->state->release();
}

} // namespace
