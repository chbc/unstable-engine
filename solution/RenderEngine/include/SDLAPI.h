#ifndef _SDLAPI_H_
#define _SDLAPI_H_

#include "AMultimediaWrapper.h"
#include <string>
#include "ImGuiAPI.h"
#include "memory_aliases.h"
#include <glm/vec2.hpp>

struct SDL_Window;

namespace sre
{

class SDLAPI : public AMultimediaWrapper
{
private:
	SDL_Window *window;
	UPTR<ImGuiAPI> imGuiAPI;

	const std::string ASSETS_FOLDER = "../../media/";

public:
	SDLAPI() = default;

protected:
	void init() override;
	void onBeginFrame() override;
	void swapBuffers() override;
	void setEditorMode(bool value) override;
	void processInput(InputHandler *inputHandler, const std::vector<GUIButtonComponent*>& guiButtons) override;
	bool checkClosePressed() override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) override;
	void log(const std::string& type, const std::string& message) override;
	void release() override;

private:
	bool checkButtonPress(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition);
	std::string getError();
};

} // namespace sre
#endif
