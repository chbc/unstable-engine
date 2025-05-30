#pragma once

#include "AMultimediaWrapper.h"
#include <string>
#include "ImGuiAPI.h"
#include "memory_aliases.h"
#include <glm/vec2.hpp>

struct SDL_Window;
union SDL_Event;

namespace sre
{

class SDLAPI : public AMultimediaWrapper
{
private:
	SDL_Window *window;
	UPTR<ImGuiAPI> imGuiAPI;

public:
	SDLAPI() : window(nullptr), imGuiAPI(nullptr) { }

protected:
	void init() override;
	void onFrameBegin() override;
	void swapBuffers() override;
	void setExecutionMode(EExecutionMode::Type mode) override;
	void processInput(const std::vector<GUIButtonComponent*>& guiButtons) override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void* loadTexture(const std::string &filePath, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) override;
	void saveTexture(void* pixels, const char* filePath, uint32_t width, uint32_t height);
	void log(const std::string& type, const std::string& message) override;
	void setMousePosition(int x, int y) override;
	void showMouseCursor(bool value) override;
	void release() override;

private:
	void processInput(const std::vector<GUIButtonComponent*>& guiButtons, SDL_Event& currentEvent);
	bool checkButtonPress(const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition);
	std::string getError();
	static bool openFileDialog(const std::string& title, const char* filter, std::string& outFileName);
	static bool saveFileDialog(const std::string& title, const char* filter, std::string& outFileName);
	static bool internalFileDialog(const std::string& title, const char* filter, bool save, std::string& outFileName);
	static void showMessageBox(const std::string& title, const std::string& message);
	static void showErrorMessageBox(const std::string& title, const std::string& message);

friend class MultimediaManager;
};

} // namespace sre
