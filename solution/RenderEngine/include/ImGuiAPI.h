#ifndef _IMGUI_API_H_
#define _IMGUI_API_H_

struct SDL_Window;
union SDL_Event;

namespace sre
{

// ImGui + SDL + OpenGL
class ImGuiAPI
{
private:
	void init(SDL_Window* window, void* glContext);
	void processEvent(SDL_Event* event);
	void onNewFrame(SDL_Window* window);
	void render();
	void release();

friend class SDLAPI;
};
	
}

#endif
