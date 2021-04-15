#include "SceneButtonComponent.h"

namespace sre
{

IMPLEMENT_COMPONENT(SceneButtonComponent)

SceneButtonComponent::SceneButtonComponent(Entity* entity, const glm::vec3& arg_extent)
	: AEntityComponent(entity), extent(arg_extent)
{

}

bool SceneButtonComponent::isInside()
{
	return false;
}

} // namespace
