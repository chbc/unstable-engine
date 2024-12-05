#pragma once

#include "memory_aliases.h"
#include <functional>

namespace sre
{

class RenderEngine;
class ScenesManager;
class RenderManager;
class MultimediaManager;
using Action = std::function<void(void*)>;

class AExecutionStrategy
{
protected:
	ScenesManager* scenesManager;
	MultimediaManager* multimediaManager;
	RenderManager* renderManager;
	SPTR<Action> entityDestroyedAction;

private:
	bool entityDestroyed;

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
	virtual void cleanUp() { }
	virtual void release() { }

private:
	void loadScene(const char* sceneName = "");
	void onEntityDestroyed(void* data);

friend class RenderEngine;
};

} // namespace
