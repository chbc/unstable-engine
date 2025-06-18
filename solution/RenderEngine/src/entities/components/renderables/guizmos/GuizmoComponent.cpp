#include "GuizmoComponent.h"

namespace sre
{

IMPLEMENT_COMPONENT(GuizmoComponent)

GuizmoComponent::GuizmoComponent(Entity* entity) : ARenderableComponent(entity)
{ }

} // namespace
