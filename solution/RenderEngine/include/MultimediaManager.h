#pragma once

#include "ASingleton.h"
#include "Timer.h"
#include "AMultimediaWrapper.h"

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
	UPTR<AMultimediaWrapper> multimediaWrapper;
	UPTR<Timer> timer;
	std::vector<GUIButtonComponent*> guiButtons;

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
	static void openFileDialog(const std::string& title, const char* filter, std::string& outFileName);

private:
	void swapBuffers();
	void setExecutionMode(EExecutionMode::Type mode);
	void processInput();
	bool checkClosePressed();
	void onFrameBegin();
    uint32_t stopTimer();
	void delay();
	uint32_t getLastFrameTime();
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp);
	void addGUIButton(GUIButtonComponent* guiButton);
	void removeDestroyedEntities();
	void cleanUp();

friend class AExecutionStrategy;
friend class EditorStrategy;
friend class ApplicationStrategy;
friend class TextureLoader;
friend class SingletonsManager;
friend class GUIButtonComponent;
};

} // namespace
