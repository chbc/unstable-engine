#pragma once

#include "AEntityComponent.h"
#include "Bounds.h"

namespace sre
{

class SRE_API ARenderableComponent : public AEntityComponent
{
protected:
	Bounds bounds{};

public:
	ARenderableComponent(Entity* entity);
	bool isRenderable() const override { return true; }
	const Bounds& getBounds() const;
};

} // namespace
