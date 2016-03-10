#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <engine/entities/renderables/materials/Material.h>
#include "VertexData.h"

namespace sre
{

class RenderManager;
class OpenGLAPI;

/*!
	Class which holds information for rendering.
*/
class Mesh
{
    private:
        RenderManager *renderManager;

        void applyMaterial(bool receiveLight);

	protected:
        std::vector<VertexData> *vertexData;
        std::vector<unsigned int> *indices;
        Material *material;

        unsigned int vbo;
        unsigned int indexBO;
        int vertexAttribLocation;
        int normalAttribLocation;

	public:
        Mesh(std::vector<VertexData> *vertexData, std::vector<unsigned int> *indices);
		~Mesh();

        void setMaterial(Material *material);

    friend class OpenGLAPI;
	friend class RenderManager;
};

} // namespace

#endif
