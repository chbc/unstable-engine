#ifndef _MESH_FACTORY_H_
#define _MESH_FACTORY_H_

#include <engine/utils/memory_aliases.h>
#include "MeshComponent.h"

namespace sre
{

class Entity;

class MeshFactory
{
public:
	static MeshComponent *createPlane(Entity *entity, float size);
	static MeshComponent *createCube(Entity *entity, float size);
};

} // namespace

#endif
