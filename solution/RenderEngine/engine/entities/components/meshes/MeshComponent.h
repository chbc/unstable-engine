#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "materials/Material.h"
#include "VertexData.h"
#include <engine/utils/memory_aliases.h>

namespace sre
{

class RenderManager;
class OpenGLAPI;
class MeshFactory;

/*!
	Class that holds information for rendering.
*/
class MeshComponent
{
    private:
		std::vector<VertexData> *vertexData;
        std::vector<unsigned int> *indices;
        UPTR<Material> material;

        unsigned int vbo;
        unsigned int indexBO;
        int vertexAttribLocation;
        int normalAttribLocation;

		bool receiveLight;

		MeshComponent(std::vector<VertexData> *vertexData, std::vector<unsigned int> *indices);

		void applyMaterial(bool receiveLight);

	public:
		~MeshComponent();

        void setMaterial(Material *material);
		void setReceiveLight(bool receiveLight);

    friend class OpenGLAPI;
	friend class RenderManager;
	friend class MeshFactory;
};

} // namespace

#endif
