#pragma once

struct SDL_Window;
union SDL_Event;

namespace sre
{

class AImGuiAPIState
{
public:
	virtual ~AImGuiAPIState() = default;

protected:
	void virtual init(SDL_Window* window, void* glContext) = 0;
	void virtual processEvent(SDL_Event* event) = 0;
	void virtual onNewFrame() = 0;
	void virtual render() = 0;
	void virtual release() = 0;

friend class ImGuiAPI;
};

} // namespace
