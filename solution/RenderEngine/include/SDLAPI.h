#ifndef _SDLAPI_H_
#define _SDLAPI_H_

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
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) override;
	void log(const std::string& type, const std::string& message) override;
	void release() override;

private:
	void processInput(const std::vector<GUIButtonComponent*>& guiButtons, SDL_Event& currentEvent);
	bool checkButtonPress(const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition);
	std::string getError();
};

} // namespace sre
#endif
