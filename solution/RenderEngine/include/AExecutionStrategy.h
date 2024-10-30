#pragma once

namespace sre
{

class RenderEngine;
class ScenesManager;
class RenderManager;
class MultimediaManager;

class AExecutionStrategy
{
protected:
	ScenesManager* scenesManager;
	MultimediaManager* multimediaManager;
	RenderManager* renderManager;

private:
	bool entityDestroyed;

protected:
	AExecutionStrategy();

protected:
	virtual void init(RenderEngine* controller) { }
	virtual inline float beginFrame(RenderEngine* controller);
	virtual inline void update(RenderEngine* controller, float elapsedTime);
	virtual inline void render(RenderEngine* controller);
	virtual inline void swapBuffers(RenderEngine* controller);
	virtual inline void endFrame(RenderEngine* controller);
	virtual inline void delay(RenderEngine* controller);
	virtual void release() { }

private:
	void loadScene(const char* fileName);


friend class RenderEngine;
};

} // namespace
