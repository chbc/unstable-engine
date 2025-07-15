#include "ARenderableComponent.h"
#include "Entity.h"

namespace sre
{

ARenderableComponent::ARenderableComponent(Entity* entity) : AEntityComponent(entity)
{ }

const Bounds& ARenderableComponent::getBounds() const
{
	return this->bounds;
}

void ARenderableComponent::setRenderActionListener(RenderAction* renderActionListener)
{
	this->onRenderAction = renderActionListener;
}

void ARenderableComponent::notifyRenderAction(AGraphicsWrapper* graphicsWrapper, ShaderManager* shaderManager, uint32_t program)
{
	if (this->onRenderAction)
	{
		(*this->onRenderAction)(graphicsWrapper, shaderManager, program);
	}
}

} // namespace
