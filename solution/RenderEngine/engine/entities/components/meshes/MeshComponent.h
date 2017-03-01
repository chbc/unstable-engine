#ifndef _MESH_H_
#define _MESH_H_

#include "../AEntityComponent.h"
#include "materials/Material.h"
#include "VertexData.h"
#include <engine/utils/memory_aliases.h>

namespace sre
{

/*!
	Class that holds information for rendering.
*/
class MeshComponent : public AEntityComponent
{
private:
	VECTOR_UPTR<VertexData> vertexData;
	std::vector<uint32_t> indices;
    UPTR<Material> material;

	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;
	
	bool receiveLight;

	MeshComponent
	(
		Entity *entity,
		VECTOR_UPTR<VertexData> &vertexData, 
		std::vector<uint32_t> &indices
	);

public:
	~MeshComponent();

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
friend class MeshFactory;
friend class Renderer;
};

} // namespace

#endif
