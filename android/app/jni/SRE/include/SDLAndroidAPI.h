#ifdef __ANDROID__

#ifndef _SDL_ANDROID_API_H_
#define _SDL_ANDROID_API_H_

#include "SDLAPI.h"

namespace sre
{

class SDLAndroidAPI : public SDLAPI
{
private:
	const std::string ASSETS_FOLDER = "media/";

public:
	SDLAndroidAPI() = default;

protected:
	void init() override;
	void processInput(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons) override;
	void* loadTexture(const std::string& fileName, uint32_t* outWidth, uint32_t* outHeight, uint8_t* outBpp) override;
	void release() override;
};

} // namespace sre
#endif
#endif
