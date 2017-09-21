#ifndef _MESH_H_
#define _MESH_H_

#include "../AEntityComponent.h"
#include "materials/Material.h"
#include <engine/utils/memory_aliases.h>
#include <engine/systems/graphics/meshData/MeshData.h>

namespace sre
{

/*!
	Class that holds information for rendering.
*/
class MeshComponent : public AEntityComponent
{
private:
	UPTR<MeshData<VertexData>> objectData;
    UPTR<Material> material;

	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;
	
	bool receiveLight;

	MeshComponent(Entity *entity, UPTR<MeshData<VertexData>> &objectData);

public:
	Material *getMaterial();
	void setMaterial(UPTR<Material> &material);
	void setReceiveLight(bool receiveLight);

	template <typename T, typename... TArgs>
	T *addMaterialComponent(TArgs&&... mArgs)
	{
		T * result = this->material->addComponent<T>(std::forward<TArgs>(mArgs)...);
		return result;
	}

friend class RenderManager;
friend class Entity;
friend class OpenGLAPI;
friend class Renderer;
friend class VertexDataFactory;
};

} // namespace

#endif
