#pragma once

#include "AExecutionStrategy.h"

namespace sre
{

class ApplicationStrategy : public AExecutionStrategy
{
public:
	ApplicationStrategy();

protected:
	void init(RenderEngine* controller) override;
	void update(RenderEngine* controller, float elapsedTime) override;
};

} // namespace
