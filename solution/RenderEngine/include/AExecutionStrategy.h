#pragma once

#include <cstdint>

namespace sre
{

class RenderEngine;
class ScenesManager;
class RenderManager;
class MultimediaManager;

class AExecutionStrategy
{
protected:
	ScenesManager* scenesManager{ nullptr };
	MultimediaManager* multimediaManager{ nullptr };
	RenderManager* renderManager{ nullptr };

protected:
	AExecutionStrategy();

protected:
	virtual void init(RenderEngine* controller) { }
	virtual inline uint32_t beginFrame(RenderEngine* controller);
	virtual inline void update(RenderEngine* controller, float elapsedTime);
	virtual inline void render(RenderEngine* controller);
	virtual inline void swapBuffers(RenderEngine* controller);
	virtual inline void endFrame(RenderEngine* controller);
	virtual inline void delay(RenderEngine* controller);
	virtual void cleanUp() {}
	virtual void release() {}

private:
	void reloadScenes();
	void loadScene(const char* scenePath);
	void loadGuiScene(const char* guiScenePath);

friend class RenderEngine;
};

} // namespace
