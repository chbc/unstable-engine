#include "transforms/TransformComponent.h"
#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/materials/Material.h>

namespace sre
{

template <typename T>
T *ComponentsFactory::create(Entity *owner)
{
	return new T{ owner };
}

template <typename T>
T *ComponentsFactory::create(Material *owner)
{
	return new T{ owner };
}

} // namespace
