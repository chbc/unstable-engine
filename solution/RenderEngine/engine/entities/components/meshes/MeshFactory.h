#ifndef _MESH_FACTORY_H_
#define _MESH_FACTORY_H_

#include <engine/utils/memory_aliases.h>

namespace sre
{

class MeshComponent;
class Entity;

class MeshFactory
{
	public:
		static MeshComponent *createPlane(Entity *entity, float size = 1.0f);
		static MeshComponent *createCube(Entity *entity, float size = 1.0f);
};

} // namespace

#endif
