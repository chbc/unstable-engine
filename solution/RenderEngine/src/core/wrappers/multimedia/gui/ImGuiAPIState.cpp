#if defined(DEBUG) && !defined(__ANDROID__)

#include "ImGuiAPIState.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include <SDL.h>

namespace sre
{

void ImGuiAPIState::init(SDL_Window* window, void* glContext)
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsClassic();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	ImVec4& windowBgColor = style.Colors[ImGuiCol_WindowBg];
	windowBgColor.w = 0.9f;
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
#endif
