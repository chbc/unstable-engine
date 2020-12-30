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
protected:
	SDL_Window *window;
	UPTR<ImGuiAPI> imGuiAPI;

private:
	const std::string ASSETS_FOLDER = "../../media/";

public:
	SDLAPI() = default;

protected:
	virtual void init() override;
	virtual void swapBuffers() override;
	virtual void processInput(InputHandler *inputHandler, const std::vector<GUIButtonComponent*>& guiButtons) override;
	bool checkClosePressed() override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) override;
	void log(const std::string& type, const std::string& message);
	virtual void release() override;

private:
	bool checkButtonPress(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition);
	std::string getError();
};

} // namespace sre
#endif
