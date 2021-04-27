#include "ImGuiAPI.h"

#include "ImGuiAPIState.h"
#include "ImGuiAPIEmptyState.h"

namespace sre
{

ImGuiAPI::ImGuiAPI()
{
	this->concreteState = make_unique<ImGuiAPIState>();
	this->emptyState = make_unique<ImGuiAPIEmptyState>();
	this->state = this->concreteState;
}

void ImGuiAPI::init(SDL_Window* window, void* glContext)
{
	this->state->init(window, glContext);
	this->setEditorMode(false);
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

void ImGuiAPI::setEditorMode(bool value)
{
	if (value)
		this->state = this->concreteState;
	else
		this->state = this->emptyState;
}

void ImGuiAPI::release()
{
	this->concreteState->release();
}

} // namespace
