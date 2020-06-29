#ifndef _AIMGUI_API_STATE_H_
#define _AIMGUI_API_STATE_H_

struct SDL_Window;
union SDL_Event;

namespace sre
{

class AImGuiAPIState
{
protected:
	void virtual init(SDL_Window* window, void* glContext) = 0;
	void virtual processEvent(SDL_Event* event) = 0;
	void virtual onNewFrame(SDL_Window* window) = 0;
	void virtual render() = 0;
	void virtual release() = 0;

friend class ImGuiAPI;
};

} // namespace

#endif
