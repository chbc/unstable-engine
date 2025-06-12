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

} // namespace
