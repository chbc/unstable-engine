#pragma once

#include "AExecutionStrategy.h"
#include "memory_aliases.h"

namespace sre
{

class WorldEditor;

class EditorStrategy : public AExecutionStrategy
{
private:
	UPTR<WorldEditor> worldEditor;

public:
	EditorStrategy();

protected:
	void init(RenderEngine* controller) override;
	void update(RenderEngine* controller, float elapsedTime) override;
	void render(RenderEngine* controller) override;
	void cleanUp() override;
	void release() override;
};

} // namespace
