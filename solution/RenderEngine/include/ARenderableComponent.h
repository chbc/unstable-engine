#pragma once

#include "AEntityComponent.h"
#include "Bounds.h"

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
using RenderAction = std::function<void(AGraphicsWrapper* graphicsWrapper, ShaderManager* shaderManager, uint32_t program)>;

class SRE_API ARenderableComponent : public AEntityComponent
{
protected:
	Bounds bounds{};
	RenderAction* onRenderAction{ nullptr };

public:
	ARenderableComponent(Entity* entity);
	bool isRenderable() const override { return true; }
	const Bounds& getBounds() const;
	void setRenderActionListener(RenderAction* renderActionListener);

private:
	void notifyRenderAction(AGraphicsWrapper* graphicsWrapper, ShaderManager* shaderManager, uint32_t program);

friend class MeshRenderer;
friend class CustomRenderer;
};

} // namespace
