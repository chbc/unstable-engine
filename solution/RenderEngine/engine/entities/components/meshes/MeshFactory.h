#ifndef _MESH_FACTORY_H_
#define _MESH_FACTORY_H_

namespace sre
{

class MeshComponent;

class MeshFactory
{
	public:
		static MeshComponent *createPlane(float size = 1.0f);
		static MeshComponent *createCube(float size = 1.0f);
};

} // namespace

#endif
