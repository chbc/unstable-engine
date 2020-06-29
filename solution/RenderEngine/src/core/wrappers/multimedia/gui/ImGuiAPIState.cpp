#include "ImGuiAPIState.h"
#include "thirdParties/imgui/imgui_impl_opengl3.h"
#include "thirdParties/imgui/imgui_impl_sdl.h"

#include <SDL/SDL.h>

namespace sre
{

	void ImGuiAPIState::init(SDL_Window* window, void* glContext)
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(window, glContext);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImGuiAPIState::processEvent(SDL_Event* event)
	{
		ImGui_ImplSDL2_ProcessEvent(event);
	}

	void ImGuiAPIState::onNewFrame(SDL_Window* window)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
	}

	void ImGuiAPIState::render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiAPIState::release()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

} // namespace
