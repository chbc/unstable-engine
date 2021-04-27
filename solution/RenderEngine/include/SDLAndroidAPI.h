#ifdef __ANDROID__

#ifndef _SDL_ANDROID_API_H_
#define _SDL_ANDROID_API_H_

#include "AMultimediaWrapper.h"
#include <glm/vec2.hpp>

struct SDL_Window;

namespace sre
{

class SDLAndroidAPI : public AMultimediaWrapper
{
private:
	SDL_Window* window;

	const std::string ASSETS_FOLDER = "media/";

public:
	SDLAndroidAPI() = default;

protected:
	void init() override;
	void onBeginFrame() override;
	void swapBuffers() override;
	void setEditorMode(bool value) override;
	void processInput(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons) override;
	bool checkClosePressed() override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void* loadTexture(const std::string& fileName, uint32_t* outWidth, uint32_t* outHeight, uint8_t* outBpp) override;
	void log(const std::string& type, const std::string& message) override;
	void release() override;

private:
	bool checkButtonPress(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition);
};

} // namespace sre
#endif
#endif
