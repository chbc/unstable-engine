#ifndef _MULTIMEDIA_MANAGER_H_
#define _MULTIMEDIA_MANAGER_H_

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

private:
	MultimediaManager() = default;

protected:
    void init() override;
    void release() override;

public:
	float getNormalizedWidth(float pixelWidth);
	glm::vec2 getNormalizedSize(const glm::vec2 &pixelSize);

	void logMessage(const std::string& message);
	void logWarning(const std::string& message);

private:
	void swapBuffers();
	void setEditorMode(bool value);
	void processInput();
	bool checkClosePressed();
	void onBeginFrame();
    uint32_t stopTimer();
	void onEndFrame();
	unsigned int getLastFrameTime();
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp);
	void addGUIButton(GUIButtonComponent* guiButton);
	void onRemoveDestroyedEntities();

friend class RenderEngine;
friend class TextureManager;
friend class SingletonsManager;
friend class GUIButtonComponent;
};

} // namespace

#endif
