#pragma once

#include "ASingleton.h"
#include "Timer.h"
#include "AMultimediaWrapper.h"
#include "AHDRTexturesWrapper.h"

#include <glm/vec2.hpp>
#include <string>

namespace sre
{

class AMultimediaWrapper;
class GUIButtonComponent;

/*!
	Class for window management
*/
class MultimediaManager : public ASingleton
{
private:
	std::vector<GUIButtonComponent*> guiButtons;
	UPTR<AMultimediaWrapper> multimediaWrapper;
	UPTR<Timer> timer;
	UPTR<AHDRTexturesWrapper> hdrTexturesWrapper;

protected:
    void init() override;
    void release() override;

public:
	float getNormalizedWidth(float pixelWidth);
	glm::vec2 getNormalizedSize(const glm::vec2 &pixelSize);

	void logMessage(const std::string& message) const;
	void logWarning(const std::string& message) const;
	static void showMessageBox(const std::string& title, const std::string& message);
	static void showErrorMessageBox(const std::string& title, const std::string& message);
	static bool openFileDialog(const std::string& title, const char* filter, std::string& outFileName);
	static bool saveFileDialog(const std::string& title, const char* filter, std::string& outFileName);
	void setMousePosition(int x, int y);
	void showMouseCursor(bool value);

private:
	void swapBuffers();
	void setExecutionMode(EExecutionMode::Type mode);
	void processInput();
	bool checkClosePressed();
	void onFrameBegin();
    uint32_t stopTimer();
	void delay();
	uint32_t getLastFrameTime();
	void* loadTexture(const std::string &filePath, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp);
	float* loadHdrTexture(const std::string& filePath, int* outWidth, int* outHeight, int* outBpp);
	void saveTexture(unsigned char* pixels, const char* filePath, uint32_t width, uint32_t height);
	void addGUIButton(GUIButtonComponent* guiButton);
	void removeDestroyedEntities();
	void cleanUp();

friend class AExecutionStrategy;
friend class EditorStrategy;
friend class ApplicationStrategy;
friend class TextureLoader;
friend class HDRTextureLoader;
friend class SingletonsManager;
friend class GUIButtonComponent;
friend class TextureCreator;
};

} // namespace
