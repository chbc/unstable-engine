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
	VECTOR_UPTR<uint32_t> indices;
    UPTR<Material> material;

    unsigned int vbo;
    unsigned int indexBO;
	
    int vertexAttribLocation;
    int normalAttribLocation;
	
	bool receiveLight;

	MeshComponent
	(
		Entity *entity,
		VECTOR_UPTR<VertexData> &vertexData, 
		VECTOR_UPTR<uint32_t> &indices
	);

	// ### void applyMaterial(bool receiveLight);

public:
	~MeshComponent();

	void setMaterial(UPTR<Material> &material);

	void setReceiveLight(bool receiveLight);

friend class RenderManager;
friend class OpenGLAPI;

/*
friend class MeshFactory;
*/
};

} // namespace

#endif